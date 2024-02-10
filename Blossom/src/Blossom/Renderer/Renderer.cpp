#include "blpch.h"
#include "Renderer.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/OpenGL/OpenGLRenderer.hpp"
#include "Blossom/APIs/Vulkan/VulkanRenderer.hpp"

namespace Blossom
{

	Renderer* Renderer::s_Instance = nullptr;
	APISpecifications Renderer::s_APISpecs = {};

	void Renderer::Init(const APISpecifications& specs)
	{
		switch (s_API)
		{
		case RenderingAPI::OpenGL:
			s_Instance = new OpenGLRenderer();
			break;
		case RenderingAPI::Vulkan:
			s_Instance = new VulkanRenderer();
			break;

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}
	}

	void Renderer::Destroy()
	{
		delete s_Instance;
	}

}