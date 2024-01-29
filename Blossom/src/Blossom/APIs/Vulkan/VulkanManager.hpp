#pragma once

#include <memory>

#include <vulkan/vulkan.h>

namespace Blossom
{

	struct VulkanDeviceInfo
	{
	public:

	};

	struct VulkanSwapChainInfo
	{
	public:

	};

	struct VulkanResourceInfo
	{
	public:
	};



	class VulkanManager
	{
	public:
		VulkanManager() = default;
		virtual ~VulkanManager() = default;

		static void Init();

		static VulkanDeviceInfo& GetDeviceInfo() { return s_Instance->m_DeviceInfo; }
		static VulkanSwapChainInfo& GetSwapChainInfo() { return s_Instance->m_SwapChainInfo; }
		static VulkanResourceInfo& GetResourceInfo() { return s_Instance->m_ResourceInfo; }

	private:
		void PopulateDeviceInfo();
		void PopulateSwapChainInfo();
		void PopulateResourceInfo();

	private:
		VulkanDeviceInfo m_DeviceInfo = {};
		VulkanSwapChainInfo m_SwapChainInfo = {};
		VulkanResourceInfo m_ResourceInfo = {};

	private:
		static std::unique_ptr<VulkanManager> s_Instance;
	};

}