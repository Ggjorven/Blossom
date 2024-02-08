#include "blpch.h"
#include "Image.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/Renderer/Renderer.hpp"

#include "Blossom/Renderer/RenderController.hpp"
#include "Blossom/Renderer/UniformBuffer.hpp"

#include "Blossom/APIs/Vulkan/VulkanImage.hpp"

namespace Blossom
{

	std::shared_ptr<Image> Image::Create(std::shared_ptr<RenderController>& controller, UniformElement& element, uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::OpenGL:
			return nullptr;
		case RenderingAPI::Vulkan:
			return std::make_shared<VulkanImage>(controller, element, width, height);

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}

		return nullptr;
	}

	std::shared_ptr<Image> Image::Create(std::shared_ptr<RenderController>& controller, UniformElement& element, const std::filesystem::path& path)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::OpenGL:
			return nullptr;
		case RenderingAPI::Vulkan:
			return std::make_shared<VulkanImage>(controller, element, path);

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}

		return nullptr;
	}

}