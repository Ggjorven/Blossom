#include "blpch.h"
#include "BaseImGuiLayer.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/Renderer/Renderer.hpp"

#include "Blossom/APIs/OpenGL/ImGui/OpenGLImGuiLayer.hpp"
#include "Blossom/APIs/Vulkan/ImGui/VulkanImGuiLayer.hpp"

namespace Blossom
{

	BaseImGuiLayer* BaseImGuiLayer::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::OpenGL:
			return new OpenGLImGuiLayer();
		case RenderingAPI::Vulkan:
			return new VulkanImGuiLayer();
			break;

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}

		return nullptr;
	}

}
