#include "blpch.h"
#include "GraphicsContext.hpp"

#include "Blossom/Core/Application.hpp"
#include "Blossom/Core/Logging.hpp"

#include "Blossom/Renderer/Renderer.hpp"

#include "Blossom/APIs/OpenGL/OpenGLContext.hpp"

namespace Blossom
{

	std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::OpenGL:
			return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
		case RenderingAPI::Vulkan:
			break;

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}

		return nullptr;
	}

}