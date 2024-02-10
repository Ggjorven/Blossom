#include "blpch.h"
#include "VulkanUniformBuffer.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/Vulkan/VulkanRenderController.hpp"
#include "Blossom/APIs/Vulkan/Setup/VulkanBufferHelper.hpp"

namespace Blossom
{

	VulkanUniformBuffer::VulkanUniformBuffer(std::shared_ptr<RenderController>& renderController, UniformElement& element, size_t dataSize)
		: m_RenderController(renderController), m_Element(element), m_Size(dataSize)
	{
		for (size_t i = 0; i < BL_MAX_FRAMES_IN_FLIGHT; i++)
		{
			VulkanBufferHelper::CreateBuffer((VkDeviceSize)dataSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VMA_MEMORY_USAGE_CPU_TO_GPU, m_Buffers[i], m_Allocations[i]);
		}
	}

	VulkanUniformBuffer::~VulkanUniformBuffer()
	{
		for (size_t i = 0; i < BL_MAX_FRAMES_IN_FLIGHT; i++)
		{
			if (m_Buffers[i] != VK_NULL_HANDLE)
				vmaDestroyBuffer(VulkanBufferHelper::GetAllocator(), m_Buffers[i], m_Allocations[i]);
		}
	}

	void VulkanUniformBuffer::SetData(void* data, size_t size)
	{
		// TODO(Jorben): Make assert?
		if (size != m_Size)
			BL_LOG_ERROR("Invalid size passed to SetData()");

		for (size_t i = 0; i < BL_MAX_FRAMES_IN_FLIGHT; i++)
		{
			// TODO(Jorben): Make this mapping function a VulkanBufferHelper function?
			void* mappedMemory = nullptr;
			if (vmaMapMemory(VulkanBufferHelper::GetAllocator(), m_Allocations[i], &mappedMemory) != VK_SUCCESS)
				BL_LOG_ERROR("Failed to map memory");

			memcpy(mappedMemory, data, size);
			vmaUnmapMemory(VulkanBufferHelper::GetAllocator(), m_Allocations[i]);
		}
	}

	void VulkanUniformBuffer::UploadToController()
	{
		auto controller = VulkanRenderController::GetController(m_RenderController);

		controller->AddUBO(m_Buffers, m_Size, m_Element.Binding, m_Element.Count);
	}

}