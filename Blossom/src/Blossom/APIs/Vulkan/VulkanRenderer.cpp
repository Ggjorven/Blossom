#include "blpch.h"
#include "VulkanRenderer.hpp"

#include <vulkan/vulkan.h>

namespace Blossom
{

	VulkanRenderer::VulkanRenderer()
	{
		m_DefaultRenderPass = new VulkanRenderPass({ 0.0f, 0.0f }, VulkanRenderPass::ColourSpace::Unorm, ColourAttachment | DepthAttachment);
	}

	VulkanRenderer::~VulkanRenderer()
	{
		delete m_DefaultRenderPass;
	}

	void VulkanRenderer::ClearImpl()
	{
		// Note(Jorben): This function is kinda redundant for vulkan so it is empty
	}

	void VulkanRenderer::SetClearColourImpl(const glm::vec4& colour)
	{
		Renderer::GetAPISpecs().ClearColour = colour;
	}

	void VulkanRenderer::UseControllerImpl(const RenderController& controller)
	{
	}

	void VulkanRenderer::OnResizeImpl(uint32_t width, uint32_t height)
	{
		// TODO recreate swapchain
	}

}