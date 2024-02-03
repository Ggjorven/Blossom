#pragma once

#include <vector>

#include "Blossom/Renderer/RenderController.hpp"

#include "Blossom/APIs/Vulkan/VulkanShader.hpp"

namespace Blossom
{

	class VulkanRenderController : public RenderController
	{
	public:
		VulkanRenderController();
		virtual ~VulkanRenderController();

		void Use() override;

		void SetShader(std::shared_ptr<Shader>& shader) override;
		void SetBufferLayout(BufferLayout& layout) override;

		void Initialize() override;

	private:
		void CreateDescriptorSetLayout();
		void CreateGraphicsPipeline();
		void CreateDescriptorPool();
		void CreateDescriptorSets();

		VkVertexInputBindingDescription GetBindingDescription();
		std::vector<VkVertexInputAttributeDescription> GetAttributeDescriptions();

	private:
		std::shared_ptr<VulkanShader> m_Shader = nullptr;
		BufferLayout m_BufferLayout = {};

		VkPipeline m_GraphicsPipeline = VK_NULL_HANDLE;
		VkPipelineLayout m_PipelineLayout = VK_NULL_HANDLE;

		std::vector<VkDescriptorSetLayout> m_DescriptorLayouts = { };
		std::vector<VkDescriptorPool> m_DescriptorPools = { };

		// Note(Jorben): The first index is the index of the descriptor and the second are VKAPP_MAX_FRAMES_INFLIGHT of sets.
		std::vector<std::vector<VkDescriptorSet>> m_DescriptorSets = { };
	};
}