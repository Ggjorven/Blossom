#pragma once

#include <vulkan/vulkan.h>

namespace Blossom
{

	class VulkanManager;
	class VulkanHelper;

	class VulkanSwapChain
	{
	public:
		inline static VulkanSwapChain* Get() { return s_Instance; }

		VulkanSwapChain();
		virtual ~VulkanSwapChain();

		void FinishSwapChainCreation();

		void RecreateSwapChain();

	private:
		void CreateSwapChain();
		void CreateImageViews();
		void CreateRenderPass();

		void CleanUp();

	private:
		static VulkanSwapChain* s_Instance;

		VkSwapchainKHR m_SwapChain = VK_NULL_HANDLE;
		VkFormat m_SwapChainImageFormat = VkFormat::VK_FORMAT_UNDEFINED;
		VkExtent2D m_SwapChainExtent = { };

		std::vector<VkImage> m_SwapChainImages = { };
		std::vector<VkImageView> m_SwapChainImageViews = { };
		
		// TODO(Jorben): Move to resource manager
		//std::vector<VkFramebuffer> m_SwapChainFramebuffers = { };

		VkRenderPass m_RenderPass = VK_NULL_HANDLE;

		friend class VulkanManager;
		friend class VulkanHelper;
	};

}