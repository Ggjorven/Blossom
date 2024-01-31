#include "blpch.h"
#include "GraphicsContext.hpp"

#include "Blossom/Core/Application.hpp"
#include "Blossom/Core/Logging.hpp"

#include "Blossom/Renderer/Renderer.hpp"

#include "Blossom/APIs/OpenGL/OpenGLContext.hpp"
#include "Blossom/APIs/Vulkan/VulkanContext.hpp"

namespace Blossom
{

	std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window, bool vsync)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::OpenGL:
			return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window), vsync);
		case RenderingAPI::Vulkan:
			return std::make_unique<VulkanContext>(static_cast<GLFWwindow*>(window), vsync);

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}

		return nullptr;
	}

}