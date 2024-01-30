#include "blpch.h"
#include "VulkanContext.hpp"

#include <GLFW/glfw3.h>

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/Vulkan/VulkanManager.hpp"

namespace Blossom
{

	VulkanContext* VulkanContext::s_Instance = nullptr;

	VulkanContext::VulkanContext(GLFWwindow* handle)
		: m_WindowHandle(handle)
	{
		s_Instance = this;
	}

	void VulkanContext::Init()
	{
		m_Instance = new VulkanInstance();
		m_SwapChain = new VulkanSwapChain();
		m_Resources = new VulkanResources();

		VulkanManager::Init();
	}

	void VulkanContext::Destroy()
	{
		delete m_Instance;
		delete m_SwapChain;
		delete m_Resources;

		s_Instance = nullptr;
	}

	void VulkanContext::SwapBuffers()
	{
	}

}
