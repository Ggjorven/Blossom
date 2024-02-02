#pragma once

#include "Blossom/Renderer/RenderController.hpp"

namespace Blossom
{

	class VulkanRenderController : public RenderController
	{
	public:
		VulkanRenderController();
		virtual ~VulkanRenderController();

		void SetShader(std::shared_ptr<Shader>& shader) override;
		void SetBufferLayout(BufferLayout& layout) override;

		void Initialize() override;

	private:
		void CreateDescriptorSetLayout();
		void CreateGraphicsPipeline();
		void CreateDescriptorPool();
		void CreateDescriptorSets();

	private:
		std::shared_ptr<Shader> m_Shader = nullptr;
		BufferLayout m_BufferLayout = {};
	};
}