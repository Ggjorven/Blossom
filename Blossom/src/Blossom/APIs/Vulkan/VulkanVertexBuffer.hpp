#pragma once

#include "Blossom/Renderer/VertexBuffer.hpp"

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

namespace Blossom
{

	class VulkanVertexBuffer : public VertexBuffer
	{
	public:
		VulkanVertexBuffer(void* data, size_t size);
		virtual ~VulkanVertexBuffer();

		void Bind() const override;
		void UnBind() const override;

		BufferLayout& GetLayout() override { return m_Layout; }
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	private:
		BufferLayout m_Layout = {};

		VkBuffer m_Buffer = VK_NULL_HANDLE;
		VmaAllocation m_BufferAllocation = VK_NULL_HANDLE;
	};
}