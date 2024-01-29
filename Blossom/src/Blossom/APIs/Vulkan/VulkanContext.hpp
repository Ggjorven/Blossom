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
		VulkanContext(GLFWwindow* handle);
		virtual ~VulkanContext() = default;

		void Init() override;
		void Destroy() override;

		void SwapBuffers() override;
		
		std::unique_ptr<VulkanInstance>& GetInstance() { return m_Instance; }
		std::unique_ptr<VulkanSwapChain>& GetSwapChain() { return m_SwapChain; }
		std::unique_ptr<VulkanResources>& GetResources() { return m_Resources; }

	private:
		GLFWwindow* m_WindowHandle = nullptr;

		std::unique_ptr<VulkanInstance> m_Instance = nullptr;
		std::unique_ptr<VulkanSwapChain> m_SwapChain = nullptr;
		std::unique_ptr<VulkanResources> m_Resources = nullptr;
	};
}