#include "blpch.h"
#include "VulkanRenderer.hpp"

#include "Blossom/Core/Logging.hpp"

#include <vulkan/vulkan.h>

#include "Blossom/Renderer/IndexBuffer.hpp"

#include "Blossom/APIs/Vulkan/VulkanContext.hpp"
#include "Blossom/APIs/Vulkan/VulkanManager.hpp"
#include "Blossom/APIs/Vulkan/Setup/VulkanResources.hpp"

#include "tracy/Tracy.hpp"

namespace Blossom
{

	VulkanRenderer* VulkanRenderer::s_Instance = nullptr;

	VulkanRenderer::VulkanRenderer()
	{
		s_Instance = this;

		VulkanSwapChainInfo& info = VulkanManager::GetSwapChainInfo();

		m_DefaultRenderPass = new VulkanRenderPass({ info.SwapChainExtent.width, info.SwapChainExtent.height }, VulkanRenderPass::ColourSpace::Unorm, ColourAttachment | DepthAttachment);
		VulkanContext::Get()->GetResources()->AddRenderPass(m_DefaultRenderPass);
	}

	VulkanRenderer::~VulkanRenderer()
	{
		delete m_DefaultRenderPass;

		s_Instance = nullptr;
	}

	void VulkanRenderer::WaitImpl()
	{
		VulkanDeviceInfo& info = VulkanManager::GetDeviceInfo();

		vkDeviceWaitIdle(info.Device);
	}

	void VulkanRenderer::ClearImpl()
	{
		//ZoneScopedN("VulkanRenderer::Clear");
		// Note(Jorben): This function is kinda redundant for vulkan so it is empty
	}

	void VulkanRenderer::SetClearColourImpl(const glm::vec4& colour)
	{
		Renderer::GetAPISpecs().ClearColour = colour;
	}

	void VulkanRenderer::DrawIndexedImpl(std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		auto& resourceInfo = VulkanManager::GetResourceInfo();

		vkCmdDrawIndexed(resourceInfo.CommandBuffers[VulkanRenderer::GetCurrentFrame()], indexBuffer->GetCount(), 1, 0, 0, 0);
	}

	void VulkanRenderer::OnResizeImpl(uint32_t width, uint32_t height)
	{
		VulkanManager::RecreateSwapChain();
	}

	void VulkanRenderer::AddToQueueImpl(RenderFunction function)
	{
		m_RenderQueue.push(function);
	}

	void VulkanRenderer::AddToUIQueueImpl(UIFunction function)
	{
		m_UIQueue.push(function);
	}

	void VulkanRenderer::DisplayImpl()
	{
		QueuePresent();
	}

	void VulkanRenderer::QueuePresent()
	{
		auto& deviceInfo = VulkanManager::GetDeviceInfo();
		auto& swapchainInfo = VulkanManager::GetSwapChainInfo();
		auto& resourceInfo = VulkanManager::GetResourceInfo();

		// Note(Jorben): Maybe getting the reference to the resourceinfo doesn't work // TODO ... check this
		vkWaitForFences(deviceInfo.Device, 1, &resourceInfo.InFlightFences[m_CurrentFrame], VK_TRUE, UINT64_MAX);

		uint32_t imageIndex;

		VkResult result = vkAcquireNextImageKHR(deviceInfo.Device, swapchainInfo.SwapChain, UINT64_MAX, resourceInfo.ImageAvailableSemaphores[m_CurrentFrame], VK_NULL_HANDLE, &imageIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			VulkanManager::RecreateSwapChain();
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			BL_LOG_ERROR("Failed to acquire swap chain image!");

		// Only reset the fence if we actually submit the work
		vkResetFences(deviceInfo.Device, 1, &resourceInfo.InFlightFences[m_CurrentFrame]);

		vkResetCommandBuffer(resourceInfo.CommandBuffers[m_CurrentFrame], 0);

		// Note(Jorben): Record the command buffer with all items in the queue
		RecordCommandBuffer(resourceInfo.CommandBuffers[m_CurrentFrame], imageIndex);

		VkSubmitInfo submitInfo = {};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[] = { resourceInfo.ImageAvailableSemaphores[m_CurrentFrame] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &resourceInfo.CommandBuffers[m_CurrentFrame];

		VkSemaphore signalSemaphores[] = { resourceInfo.RenderFinishedSemaphores[m_CurrentFrame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		if (vkQueueSubmit(deviceInfo.GraphicsQueue, 1, &submitInfo, resourceInfo.InFlightFences[m_CurrentFrame]) != VK_SUCCESS)
			BL_LOG_ERROR("Failed to submit draw command buffer!");

		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[] = { swapchainInfo.SwapChain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;
		presentInfo.pImageIndices = &imageIndex;
		presentInfo.pResults = nullptr; // Optional

		// Check for the result on present again
		result = vkQueuePresentKHR(deviceInfo.PresentQueue, &presentInfo);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
			VulkanManager::RecreateSwapChain();
		else if (result != VK_SUCCESS)
			BL_LOG_ERROR("Failed to present swap chain image!");

		// Note(Jorben): We use the & operator since MAX_FRAMES_IN_FLIGHT is a power of 2 and this is a lot cheaper, if it's not use the % operator
		m_CurrentFrame = (m_CurrentFrame + 1) & BL_MAX_FRAMES_IN_FLIGHT;
	}

	void VulkanRenderer::RecordCommandBuffer(VkCommandBuffer& commandBuffer, uint32_t imageIndex)
	{
		VulkanSwapChainInfo& swapchainInfo = VulkanManager::GetSwapChainInfo();

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
			BL_LOG_ERROR("Failed to begin recording command buffer!");

		//
		// TODO(Jorben): Create a custom way to start a render pass
		//
		VulkanRenderPass* renderPass = VulkanContext::Get()->GetResources()->GetRenderPasses()[0]; // Get the first one for now

		std::vector<VkClearValue> clearValues = {};
		if (renderPass->HasDepth()) clearValues.resize(2);
		else clearValues.resize(1);

		APISpecifications specs = Renderer::GetAPISpecs();
		clearValues[0].color = { {specs.ClearColour.r, specs.ClearColour.g, specs.ClearColour.b, specs.ClearColour.a} };
		
		if (renderPass->HasDepth())
		{
			clearValues[1].depthStencil = { 1.0f, 0 };
		}

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = renderPass->m_RenderPass;
		renderPassInfo.framebuffer = renderPass->m_SwapChainFramebuffers[imageIndex];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = swapchainInfo.SwapChainExtent;

		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		VkViewport viewport = {};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)swapchainInfo.SwapChainExtent.width;
		viewport.height = (float)swapchainInfo.SwapChainExtent.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

		VkRect2D scissor = {};
		scissor.offset = { 0, 0 };
		scissor.extent = swapchainInfo.SwapChainExtent;
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

		// Execute all commands
		while (!m_RenderQueue.empty())
		{
			auto& func = m_RenderQueue.front();
			func();
			m_RenderQueue.pop();
		}
		while (!m_UIQueue.empty())
		{
			auto& func = m_UIQueue.front();
			func();
			m_UIQueue.pop();
		}

		vkCmdEndRenderPass(commandBuffer);

		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
			BL_LOG_ERROR("Failed to record command buffer!");
	}

}