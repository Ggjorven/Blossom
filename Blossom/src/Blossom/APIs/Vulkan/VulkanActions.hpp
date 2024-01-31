#pragma once

#include <vulkan/vulkan.h>

namespace Blossom
{

	class VulkanActions
	{
	public:
		static VkCommandBuffer BeginSingleTimeCommands();
		static void EndSingleTimeCommands(VkCommandBuffer& buffer);
	};
}