#include "blpch.h"
#include "Renderer.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/OpenGL/OpenGLRenderer.hpp"

namespace Blossom
{

	std::unique_ptr<Renderer> Renderer::s_Instance = nullptr;
	RenderingAPI Renderer::s_API = RenderingAPI::OpenGL; // Note(Jorben): This is where the API is selected.
	APISpecifications Renderer::s_APISpecs = {};

	void Renderer::Init(const APISpecifications& specs)
	{
		switch (s_API)
		{
		case RenderingAPI::OpenGL:
			s_Instance = std::make_unique<OpenGLRenderer>();
			break;
		case RenderingAPI::Vulkan:
			break;

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}
	}

}