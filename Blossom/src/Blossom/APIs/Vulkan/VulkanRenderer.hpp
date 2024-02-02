#pragma once

#include <queue>

#include "Blossom/Renderer/Renderer.hpp"

#include "Blossom/APIs/Vulkan/VulkanRenderPass.hpp"

namespace Blossom
{

	class VulkanRenderer : public Renderer
	{
	public:
		static VulkanRenderer* Get() { return s_Instance; }

		VulkanRenderer();
		virtual ~VulkanRenderer();

		static uint32_t GetCurrentFrame() { return s_Instance->m_CurrentFrame; }
	
	private:
		void ClearImpl() override;
		void SetClearColourImpl(const glm::vec4& colour) override;

		void UseControllerImpl(const RenderController& controller) override;

		void DrawIndexedImpl(std::shared_ptr<IndexBuffer>& indexBuffer) override;

		void OnResizeImpl(uint32_t width, uint32_t height) override;

		void AddToQueueImpl(RenderFunction function) override;
		void AddToUIQueueImpl(UIFunction function) override;

		void DisplayImpl() override;

	private:
		void QueuePresent();
		void RecordCommandBuffer(VkCommandBuffer& commandBuffer, uint32_t imageIndex);

	private:
		static VulkanRenderer* s_Instance;

		uint32_t m_CurrentFrame = 0;

		VulkanRenderPass* m_DefaultRenderPass;

		std::queue<RenderFunction> m_RenderQueue = { };
		std::queue<UIFunction> m_UIQueue = { };
	};

}