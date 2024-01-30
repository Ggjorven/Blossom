#pragma once

#include <optional>
#include <vector>

#include <vulkan/vulkan.h>

namespace Blossom
{

	class VulkanInstance;

	class VulkanHelper
	{
	public:
		struct QueueFamilyIndices
		{
		public:
			std::optional<uint32_t> GraphicsFamily;
			std::optional<uint32_t> PresentFamily;

			static QueueFamilyIndices Find(VulkanInstance* instance, const VkPhysicalDevice& device);

		public:
			inline bool IsComplete() const { return GraphicsFamily.has_value() && PresentFamily.has_value(); }
		};

		struct SwapChainSupportDetails
		{
		public:
			VkSurfaceCapabilitiesKHR Capabilities;
			std::vector<VkSurfaceFormatKHR> Formats;
			std::vector<VkPresentModeKHR> PresentModes;

			static SwapChainSupportDetails Query(VulkanInstance* instance, const VkPhysicalDevice& device);
		};

	public:
		static bool ValidationLayersSupported();
		static std::vector<const char*> GetRequiredExtensions();
		static bool PhysicalDeviceSuitable(VulkanInstance* instance, const VkPhysicalDevice& device);
		static bool ExtensionsSupported(const VkPhysicalDevice& device);

	};
}