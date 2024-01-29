#include "blpch.h"
#include "VulkanManager.hpp"

namespace Blossom
{

	std::unique_ptr<VulkanManager> VulkanManager::s_Instance = nullptr;

	void VulkanManager::Init()
	{
		s_Instance = std::make_unique<VulkanManager>();

		s_Instance->PopulateDeviceInfo();
		s_Instance->PopulateSwapChainInfo();
		s_Instance->PopulateResourceInfo();
	}

	void VulkanManager::PopulateDeviceInfo()
	{
	}

	void VulkanManager::PopulateSwapChainInfo()
	{
	}

	void VulkanManager::PopulateResourceInfo()
	{
	}

}