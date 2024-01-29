#pragma once

#include <memory>

#include "Blossom/Renderer/GraphicsContext.hpp"

#include "Blossom/APIs/Vulkan/Setup/VulkanInstance.hpp"

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

	private:
		GLFWwindow* m_WindowHandle = nullptr;

		std::unique_ptr<VulkanInstance> m_Instance = nullptr;
	};
}