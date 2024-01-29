#include "blpch.h"
#include "VulkanContext.hpp"

#include <GLFW/glfw3.h>

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/Vulkan/VulkanManager.hpp"

namespace Blossom
{

	VulkanContext::VulkanContext(GLFWwindow* handle)
		: m_WindowHandle(handle)
	{
	}

	void VulkanContext::Init()
	{
		m_Instance = std::make_unique<VulkanInstance>();
		m_SwapChain = std::make_unique<VulkanSwapChain>();
		m_Resources = std::make_unique<VulkanResources>();

		VulkanManager::Init();
	}

	void VulkanContext::Destroy()
	{
	}

	void VulkanContext::SwapBuffers()
	{
	}

}
