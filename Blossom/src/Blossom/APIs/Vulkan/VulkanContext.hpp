#pragma once

#include <memory>

#include "Blossom/Renderer/GraphicsContext.hpp"

#include "Blossom/APIs/Vulkan/Setup/VulkanInstance.hpp"
#include "Blossom/APIs/Vulkan/Setup/VulkanSwapChain.hpp"
#include "Blossom/APIs/Vulkan/Setup/VulkanResources.hpp"

#include <GLFW/glfw3.h>

namespace Blossom
{

	class VulkanContext : public GraphicsContext
	{
	public:
		inline static VulkanContext* Get() { return s_Instance; }

		VulkanContext(GLFWwindow* handle);
		virtual ~VulkanContext() = default;

		void Init() override;
		void Destroy() override;

		void SwapBuffers() override;
		
		VulkanInstance*& GetInstance() { return m_Instance; }
		VulkanSwapChain*& GetSwapChain() { return m_SwapChain; }
		VulkanResources*& GetResources() { return m_Resources; }

		GLFWwindow* GetWindowHandle() { return m_WindowHandle; }

	private:
		static VulkanContext* s_Instance;

		GLFWwindow* m_WindowHandle = nullptr;

		VulkanInstance* m_Instance = nullptr;
		VulkanSwapChain* m_SwapChain = nullptr;
		VulkanResources* m_Resources = nullptr;
	};
}