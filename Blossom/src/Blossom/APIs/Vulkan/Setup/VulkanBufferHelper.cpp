#include "blpch.h"
#include "VulkanImageHelper.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/Vulkan/VulkanManager.hpp"
#include "Blossom/APIs/Vulkan/VulkanActions.hpp"
#include "VulkanBufferHelper.hpp"

namespace Blossom
{
	uint32_t Blossom::VulkanBufferHelper::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
		VkPhysicalDeviceMemoryProperties memProperties = {};
		vkGetPhysicalDeviceMemoryProperties(VulkanManager::GetDeviceInfo().PhysicalDevice, &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
		{
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
				return i;
		}

		BL_LOG_ERROR("Failed to find suitable memory type!");
		return -1;
	}
}