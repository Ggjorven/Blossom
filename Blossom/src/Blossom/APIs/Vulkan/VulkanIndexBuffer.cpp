#include "blpch.h"
#include "VulkanIndexBuffer.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/Vulkan/VulkanManager.hpp"
#include "Blossom/APIs/Vulkan/VulkanRenderer.hpp"
#include "Blossom/APIs/Vulkan/Setup/VulkanBufferHelper.hpp"

namespace Blossom
{

	VulkanIndexBuffer::VulkanIndexBuffer(uint32_t* data, uint32_t count)
	{
        VkDeviceSize bufferSize = sizeof(uint32_t) * count;
        VulkanBufferHelper::CreateBuffer(bufferSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VMA_MEMORY_USAGE_GPU_ONLY, m_Buffer, m_BufferAllocation);

        VkBuffer stagingBuffer = VK_NULL_HANDLE;
        VmaAllocation stagingBufferAllocation = VK_NULL_HANDLE;
        VulkanBufferHelper::CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_MEMORY_USAGE_CPU_ONLY, stagingBuffer, stagingBufferAllocation);

        // Map the staging buffer and copy the data to it
        void* mappedData;
        vmaMapMemory(VulkanBufferHelper::GetAllocator(), stagingBufferAllocation, &mappedData);
        memcpy(mappedData, data, bufferSize);
        vmaUnmapMemory(VulkanBufferHelper::GetAllocator(), stagingBufferAllocation);

        // Copy data from the staging buffer to the index buffer
        VulkanBufferHelper::CopyBuffer(stagingBuffer, m_Buffer, bufferSize);

        // Clean up the staging buffer
        vmaDestroyBuffer(VulkanBufferHelper::GetAllocator(), stagingBuffer, stagingBufferAllocation);
	}

	VulkanIndexBuffer::~VulkanIndexBuffer()
	{
        if (m_Buffer != VK_NULL_HANDLE)
            vmaDestroyBuffer(VulkanBufferHelper::GetAllocator(), m_Buffer, m_BufferAllocation);
	}

	void VulkanIndexBuffer::Bind() const
	{
        auto& resourceInfo = VulkanManager::GetResourceInfo();

        vkCmdBindIndexBuffer(resourceInfo.CommandBuffers[VulkanRenderer::GetCurrentFrame()], m_Buffer, 0, VK_INDEX_TYPE_UINT32);
	}

	void VulkanIndexBuffer::UnBind() const
	{
        // Note(Jorben): This function is irrelevant for Vulkan
	}

}