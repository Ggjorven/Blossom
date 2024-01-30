#include "blpch.h"
#include "VulkanSwapChain.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/Vulkan/Setup/VulkanInstance.hpp"
#include "Blossom/APIs/Vulkan/Setup/VulkanHelper.hpp"
#include "Blossom/APIs/Vulkan/VulkanContext.hpp"
#include "Blossom/APIs/Vulkan/VulkanManager.hpp"

namespace Blossom
{

	VulkanSwapChain* VulkanSwapChain::s_Instance = nullptr;

	VulkanSwapChain::VulkanSwapChain()
	{
		s_Instance = this;

		CreateSwapChain();
		// ...
	}

	VulkanSwapChain::~VulkanSwapChain()
	{
		CleanUp();

		vkDestroyRenderPass(VulkanManager::GetDeviceInfo().Device, m_RenderPass, nullptr);

		s_Instance = nullptr;
	}

	void VulkanSwapChain::FinishSwapChainCreation()
	{
		//CreateFramebuffers();
	}

	void VulkanSwapChain::RecreateSwapChain()
	{
		CleanUp();

		CreateSwapChain();
		// ...
	}

	void VulkanSwapChain::CreateSwapChain()
	{
		VulkanDeviceInfo& info = VulkanManager::GetDeviceInfo();

		VulkanHelper::SwapChainSupportDetails swapChainSupport = VulkanHelper::SwapChainSupportDetails::Query(VulkanContext::Get()->GetInstance(), info.PhysicalDevice);

		VkSurfaceFormatKHR surfaceFormat = VulkanHelper::ChooseSwapSurfaceFormat(swapChainSupport.Formats);
		VkPresentModeKHR presentMode = VulkanHelper::ChooseSwapPresentMode(swapChainSupport.PresentModes);
		VkExtent2D extent = VulkanHelper::ChooseSwapExtent(swapChainSupport.Capabilities);

		// Note(Jorben): +1 because sticking to the minimum can cause us to wait on the driver sometimes
		uint32_t imageCount = swapChainSupport.Capabilities.minImageCount + 1;

		// Making sure we don't exceed the maximum
		if (swapChainSupport.Capabilities.maxImageCount > 0 && imageCount > swapChainSupport.Capabilities.maxImageCount)
			imageCount = swapChainSupport.Capabilities.maxImageCount;

		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = info.Surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		VulkanHelper::QueueFamilyIndices indices = VulkanHelper::QueueFamilyIndices::Find(VulkanContext::Get()->GetInstance(), info.PhysicalDevice);
		uint32_t queueFamilyIndices[] = { indices.GraphicsFamily.value(), indices.PresentFamily.value() };

		if (indices.GraphicsFamily != indices.PresentFamily)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0; // Optional
			createInfo.pQueueFamilyIndices = nullptr; // Optional
		}

		createInfo.preTransform = swapChainSupport.Capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		createInfo.oldSwapchain = VK_NULL_HANDLE;

		// Creation of the swapchain
		if (vkCreateSwapchainKHR(info.Device, &createInfo, nullptr, &m_SwapChain) != VK_SUCCESS)
			BL_LOG_ERROR("Failed to create swap chain!");

		// Note(Jorben): We query the amount of images again, because vulkan is allowed to create a swapchain with more images.
		vkGetSwapchainImagesKHR(info.Device, m_SwapChain, &imageCount, nullptr);
		m_SwapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(info.Device, m_SwapChain, &imageCount, m_SwapChainImages.data());

		// Store the format and extent for the future
		m_SwapChainImageFormat = surfaceFormat.format;
		m_SwapChainExtent = extent;
	}

	void VulkanSwapChain::CreateImageViews()
	{
		// TODO(Jorben): Implement the buffermanager function somewhere

		//m_SwapChainImageViews.resize(m_SwapChainImages.size());
		//
		//for (size_t i = 0; i < m_SwapChainImages.size(); i++)
		//{
		//	m_SwapChainImageViews[i] = BufferManager::CreateImageView(m_SwapChainImages[i], m_SwapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
		//}
	}

	void VulkanSwapChain::CreateRenderPass()
	{
		// Colour
		VkAttachmentDescription colorAttachment = {};
		colorAttachment.format = m_SwapChainImageFormat;
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef = {};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		// Depth
		VkAttachmentDescription depthAttachment = {};
		depthAttachment.format = VulkanHelper::FindDepthFormat();
		depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		VkAttachmentReference depthAttachmentRef = {};
		depthAttachmentRef.attachment = 1;
		depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

		// Subpass
		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;
		subpass.pDepthStencilAttachment = &depthAttachmentRef;

		VkSubpassDependency dependency = {};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

		std::array<VkAttachmentDescription, 2> attachments = { colorAttachment, depthAttachment };

		VkRenderPassCreateInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
		renderPassInfo.pAttachments = attachments.data();
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

		if (vkCreateRenderPass(VulkanManager::GetDeviceInfo().Device, &renderPassInfo, nullptr, &m_RenderPass) != VK_SUCCESS)
			BL_LOG_ERROR("Failed to create render pass!");
	}

	// TODO(Jorben): Move framebuffers to resources
	// 
	//void VulkanSwapChain::CreateFramebuffers()
	//{
	//	m_SwapChainFramebuffers.resize(m_SwapChainImageViews.size());
	//
	//	for (size_t i = 0; i < m_SwapChainImageViews.size(); i++)
	//	{
	//		std::array<VkImageView, 2> attachments = { m_SwapChainImageViews[i], m_DepthImageView };
	//
	//		VkFramebufferCreateInfo framebufferInfo = {};
	//		framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	//		framebufferInfo.renderPass = m_RenderPass;
	//		framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
	//		framebufferInfo.pAttachments = attachments.data();
	//		framebufferInfo.width = m_SwapChainExtent.width;
	//		framebufferInfo.height = m_SwapChainExtent.height;
	//		framebufferInfo.layers = 1;
	//
	//		if (vkCreateFramebuffer(s_InstanceManager->m_Device, &framebufferInfo, nullptr, &m_SwapChainFramebuffers[i]) != VK_SUCCESS)
	//			VKAPP_LOG_ERROR("Failed to create framebuffer!");
	//	}
	//}

	void VulkanSwapChain::CleanUp()
	{
		VulkanDeviceInfo& info = VulkanManager::GetDeviceInfo();

		// TODO(Jorben): Move to Resources
		//vkDestroyImageView(s_InstanceManager->m_Device, m_DepthImageView, nullptr);
		//vkDestroyImage(s_InstanceManager->m_Device, m_DepthImage, nullptr);
		//vkFreeMemory(s_InstanceManager->m_Device, m_DepthImageMemory, nullptr);

		//for (size_t i = 0; i < m_SwapChainFramebuffers.size(); i++)
		//	vkDestroyFramebuffer(info.Device, m_SwapChainFramebuffers[i], nullptr);

		for (size_t i = 0; i < m_SwapChainImageViews.size(); i++)
			vkDestroyImageView(info.Device, m_SwapChainImageViews[i], nullptr);

		vkDestroySwapchainKHR(info.Device, m_SwapChain, nullptr);
	}

}