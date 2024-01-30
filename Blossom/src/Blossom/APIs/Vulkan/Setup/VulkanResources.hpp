#pragma once

#include <memory>

#include <vulkan/vulkan.h>

#include "Blossom/APIs/Vulkan/VulkanRenderPass.hpp"

namespace Blossom
{

	#define BL_MAX_FRAMES_IN_FLIGHT 2

	class VulkanManager;
	class VulkanHelper;

	class VulkanResources
	{
	public:
		VulkanResources();
		virtual ~VulkanResources();

		void AddRenderPass(VulkanRenderPass* renderpass);

		void RecreateFramebuffers();

	private:
		void CreateCommandPool();
		void CreateCommandBuffers();
		void CreateSyncObjects();

	private:
		uint32_t m_CurrentFrame = 0;

		VkCommandPool m_CommandPool = VK_NULL_HANDLE;
		std::vector<VkCommandBuffer> m_CommandBuffers = { };

		// Used for synchronization
		std::vector<VkSemaphore> m_ImageAvailableSemaphores = { };
		std::vector<VkSemaphore> m_RenderFinishedSemaphores = { };
		std::vector<VkFence> m_InFlightFences = { };

		// All renderpasses // TODO(Jorben): Have a better system
		std::vector<VulkanRenderPass*> m_RenderPasses = { };

		friend class VulkanManager;
		friend class VulkanHelper;
	};

}