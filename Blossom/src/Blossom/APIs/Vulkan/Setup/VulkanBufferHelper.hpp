#pragma once

#include <vulkan/vulkan.h>

namespace Blossom
{

	class VulkanBufferHelper
	{
	public:
		static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	};

}