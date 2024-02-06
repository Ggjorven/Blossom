#include "blpch.h"
#include "UniformBuffer.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/Renderer/Renderer.hpp"

#include "Blossom/APIs/Vulkan/VulkanUniformBuffer.hpp"

namespace Blossom
{

	std::shared_ptr<UniformBufferObject> UniformBufferObject::Create(std::shared_ptr<RenderController>& controller, UniformElement& element, size_t dataSize)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::OpenGL:
			return nullptr; // TODO(Jorben): Implement
		case RenderingAPI::Vulkan:
			return std::make_shared<VulkanUniformBuffer>(controller, element, dataSize); // TODO(Jorben): Implement

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}

		return nullptr;
	}

}