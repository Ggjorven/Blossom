#include "blpch.h"
#include "RenderController.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/Renderer/Renderer.hpp"

#include "Blossom/APIs/OpenGL/OpenGLRenderController.hpp"

namespace Blossom
{

	std::shared_ptr<RenderController> RenderController::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::OpenGL:
			return std::make_shared<OpenGLRenderController>();
		case RenderingAPI::Vulkan:
			return nullptr;

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}

		return nullptr;
	}

}