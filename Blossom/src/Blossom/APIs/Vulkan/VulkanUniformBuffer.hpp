#pragma once

#include <array>

#include "Blossom/Renderer/RenderController.hpp"
#include "Blossom/Renderer/UniformBuffer.hpp"
#include "Blossom/APIs/Vulkan/Setup/VulkanResources.hpp"

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

namespace Blossom
{

	class VulkanUniformBuffer : public UniformBufferObject
	{
	public:
		VulkanUniformBuffer(std::shared_ptr<RenderController>& renderController, UniformElement& element, size_t dataSize);
		virtual ~VulkanUniformBuffer();

		void SetData(void* data, size_t size);
		void UploadToController();

	private:
		std::shared_ptr<RenderController>& m_RenderController;
		UniformElement& m_Element;
		size_t m_Size = 0;

		std::array<VkBuffer, BL_MAX_FRAMES_IN_FLIGHT> m_Buffers = { };
		std::array<VmaAllocation, BL_MAX_FRAMES_IN_FLIGHT> m_Allocations = { };
	};
}