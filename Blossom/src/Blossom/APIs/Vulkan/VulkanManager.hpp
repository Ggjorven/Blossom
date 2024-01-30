#pragma once

#include <memory>
#include <vector>

#include <vulkan/vulkan.h>

namespace Blossom
{

	struct VulkanDeviceInfo
	{
	public:
		VkInstance Instance = VK_NULL_HANDLE;
		VkDebugUtilsMessengerEXT DebugMessenger = VK_NULL_HANDLE;
		VkSurfaceKHR Surface = VK_NULL_HANDLE;

		VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
		VkDevice Device = VK_NULL_HANDLE;

		VkQueue GraphicsQueue = VK_NULL_HANDLE;
		VkQueue PresentQueue = VK_NULL_HANDLE;
	};

	struct VulkanSwapChainInfo
	{
	public:
		VkSwapchainKHR SwapChain = VK_NULL_HANDLE;
		VkFormat SwapChainImageFormat = VkFormat::VK_FORMAT_UNDEFINED;
		VkExtent2D SwapChainExtent = { };

		std::vector<VkImage> SwapChainImages = { };
		std::vector<VkImageView> SwapChainImageViews = { };
		std::vector<VkFramebuffer> SwapChainFramebuffers = { };

		VkRenderPass RenderPass = VK_NULL_HANDLE;
	};

	struct VulkanResourceInfo
	{
	public:
		// TODO: ...
		VkImageView DepthImageView = VK_NULL_HANDLE;
	};



	class VulkanManager
	{
	public:
		VulkanManager() = default;
		virtual ~VulkanManager() = default;

		static void Init();

		static void RecreateSwapChain();

		static VulkanDeviceInfo& GetDeviceInfo() { return s_Instance->m_DeviceInfo; }
		static VulkanSwapChainInfo& GetSwapChainInfo() { return s_Instance->m_SwapChainInfo; }
		static VulkanResourceInfo& GetResourceInfo() { return s_Instance->m_ResourceInfo; }

		static void PopulateDeviceInfo();
		static void PopulateSwapChainInfo();
		static void PopulateResourceInfo();

	private:
		VulkanDeviceInfo m_DeviceInfo = {};
		VulkanSwapChainInfo m_SwapChainInfo = {};
		VulkanResourceInfo m_ResourceInfo = {};

	private:
		static std::unique_ptr<VulkanManager> s_Instance;
	};

}