#include "blpch.h"
#include "VulkanVertexBuffer.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/Vulkan/VulkanManager.hpp"
#include "Blossom/APIs/Vulkan/VulkanRenderer.hpp"
#include "Blossom/APIs/Vulkan/Setup/VulkanBufferHelper.hpp"

namespace Blossom
{

	VulkanVertexBuffer::VulkanVertexBuffer(void* data, size_t size)
	{
        VulkanBufferHelper::CreateBuffer(size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VMA_MEMORY_USAGE_GPU_ONLY, m_Buffer, m_BufferAllocation);

        VkBuffer stagingBuffer = VK_NULL_HANDLE;
        VmaAllocation stagingBufferAllocation = VK_NULL_HANDLE;
        VulkanBufferHelper::CreateBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_MEMORY_USAGE_CPU_ONLY, stagingBuffer, stagingBufferAllocation);

        void* mappedData;
        vmaMapMemory(VulkanBufferHelper::GetAllocator(), stagingBufferAllocation, &mappedData);
        memcpy(mappedData, data, size);
        vmaUnmapMemory(VulkanBufferHelper::GetAllocator(), stagingBufferAllocation);

        VulkanBufferHelper::CopyBuffer(stagingBuffer, m_Buffer, size);

        vmaDestroyBuffer(VulkanBufferHelper::GetAllocator(), stagingBuffer, stagingBufferAllocation);
	}

	VulkanVertexBuffer::~VulkanVertexBuffer()
	{
		if (m_Buffer != VK_NULL_HANDLE)
			vmaDestroyBuffer(VulkanBufferHelper::GetAllocator(), m_Buffer, m_BufferAllocation);
	}

	void VulkanVertexBuffer::Bind() const
	{
		auto& resourceInfo = VulkanManager::GetResourceInfo();

		VkBuffer buffers[] = { m_Buffer };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(resourceInfo.CommandBuffers[VulkanRenderer::GetCurrentFrame()], 0, 1, buffers, offsets);
	}

	void VulkanVertexBuffer::UnBind() const
	{
		// Note(Jorben): This function is irrelevant for Vulkan
	}

}