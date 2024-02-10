#include "blpch.h"
#include "UniformBuffer.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/Renderer/Renderer.hpp"

#include "Blossom/APIs/Vulkan/VulkanUniformBuffer.hpp"
#include "Blossom/APIs/OpenGL/OpenGLUniformBuffer.hpp"

namespace Blossom
{

	std::shared_ptr<UniformBufferObject> UniformBufferObject::Create(std::shared_ptr<RenderController>& controller, UniformElement& element, size_t dataSize)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::OpenGL:
			return std::make_shared<OpenGLUniformBuffer>(controller, element, dataSize);
		case RenderingAPI::Vulkan:
			return std::make_shared<VulkanUniformBuffer>(controller, element, dataSize);

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}

		return nullptr;
	}

}