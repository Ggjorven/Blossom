#pragma once

#include "Blossom/Renderer/Renderer.hpp"

#include "Blossom/APIs/Vulkan/VulkanRenderPass.hpp"

namespace Blossom
{

	class VulkanRenderer : public Renderer
	{
	public:
		VulkanRenderer();
		virtual ~VulkanRenderer();

	private:
		void ClearImpl() override;
		void SetClearColourImpl(const glm::vec4& colour) override;

		void UseControllerImpl(const RenderController& controller) override;

		void OnResizeImpl(uint32_t width, uint32_t height) override;

	private:
		VulkanRenderPass* m_DefaultRenderPass;
	};

}