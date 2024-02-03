#include "blpch.h"
#include "VulkanContext.hpp"

#include <GLFW/glfw3.h>

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/Vulkan/VulkanManager.hpp"
#include "Blossom/APIs/Vulkan/Setup/VulkanBufferHelper.hpp"

namespace Blossom
{

	VulkanContext* VulkanContext::s_Instance = nullptr;

	VulkanContext::VulkanContext(GLFWwindow* handle, bool vsync)
		: m_WindowHandle(handle)
	{
		s_Instance = this;
	}

	void VulkanContext::Init()
	{
		VulkanManager::Init();

		m_Instance = new VulkanInstance();
		VulkanManager::PopulateDeviceInfo();

		m_SwapChain = new VulkanSwapChain();
		VulkanManager::PopulateSwapChainInfo();

		m_Resources = new VulkanResources();
		VulkanManager::PopulateResourceInfo();

		VulkanManager::InitProfiler();
		VulkanBufferHelper::Init();
	}

	void VulkanContext::Destroy()
	{
		VulkanBufferHelper::Destroy();

		delete m_SwapChain;
		delete m_Resources;
		delete m_Instance;

		s_Instance = nullptr;
	}

	void VulkanContext::SwapBuffers()
	{
	}

}
