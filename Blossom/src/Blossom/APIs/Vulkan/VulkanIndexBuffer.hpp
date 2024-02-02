#pragma once

#include "Blossom/Renderer/IndexBuffer.hpp"

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

namespace Blossom
{

	class VulkanIndexBuffer : public IndexBuffer
	{
	public:
		VulkanIndexBuffer(uint32_t* data, uint32_t count);
		virtual ~VulkanIndexBuffer();

		void Bind() const;
		void UnBind() const;

		uint32_t GetCount() const { return m_Count; }

	private:
		VkBuffer m_Buffer = VK_NULL_HANDLE;
		VmaAllocation m_BufferAllocation = VK_NULL_HANDLE;

		uint32_t m_Count = 0;
	};
}