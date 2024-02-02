#include "blpch.h"
#include "IndexBuffer.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/Renderer/Renderer.hpp"

#include "Blossom/APIs/OpenGL/OpenGLIndexBuffer.hpp"

namespace Blossom
{

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, count);
		case RenderingAPI::Vulkan:
			return nullptr;

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}

		return nullptr;
	}

}