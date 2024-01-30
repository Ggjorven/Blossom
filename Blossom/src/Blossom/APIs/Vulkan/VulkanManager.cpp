#include "blpch.h"
#include "VulkanManager.hpp"

#include "Blossom/APIs/Vulkan/VulkanContext.hpp"

namespace Blossom
{

	std::unique_ptr<VulkanManager> VulkanManager::s_Instance = nullptr;

	void VulkanManager::Init()
	{
		s_Instance = std::make_unique<VulkanManager>();
	}

	void VulkanManager::RecreateSwapChain()
	{
		VulkanSwapChain& vc = *VulkanContext::Get()->GetSwapChain();
		vc.RecreateSwapChain();

		// TODO(Jorben): Recreate the depth and colour resources
		// TODO(Jorben): Recreate the framebuffers (of renderpasses)
	}

	void VulkanManager::PopulateDeviceInfo()
	{
		VulkanInstance& vc = *VulkanContext::Get()->GetInstance();
		
		VulkanDeviceInfo deviceInfo = {};
		deviceInfo.Instance = vc.m_Instance;
		deviceInfo.DebugMessenger = vc.m_DebugMessenger;
		deviceInfo.Surface = vc.m_Surface;

		deviceInfo.PhysicalDevice = vc.m_PhysicalDevice;
		deviceInfo.Device = vc.m_Device;

		deviceInfo.GraphicsQueue = vc.m_GraphicsQueue;
		deviceInfo.PresentQueue = vc.m_PresentQueue;

		s_Instance->m_DeviceInfo = deviceInfo;
	}

	void VulkanManager::PopulateSwapChainInfo()
	{
		VulkanSwapChain& vc = *VulkanContext::Get()->GetSwapChain();

		VulkanSwapChainInfo swapchainInfo = {};
		
		// ... TODO

		s_Instance->m_SwapChainInfo = swapchainInfo;
	}

	void VulkanManager::PopulateResourceInfo()
	{
	}

}