#pragma once

#include <array>
#include <vector>

#include "Blossom/Renderer/RenderController.hpp"

#include "Blossom/APIs/Vulkan/VulkanShader.hpp"
#include "Blossom/APIs/Vulkan/Setup/VulkanResources.hpp"

#include <vulkan/vulkan.h>

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
		void SetUniformLayout(UniformLayout& layout) override;

		void Initialize() override;

		void AddUBO(std::array<VkBuffer, BL_MAX_FRAMES_IN_FLIGHT>& buffers, size_t size, uint32_t binding = 0, uint32_t count = 1);

		static std::shared_ptr<VulkanRenderController> GetController(std::shared_ptr<RenderController>& renderController);

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
		UniformLayout m_UniformLayout = {};

		VkPipeline m_GraphicsPipeline = VK_NULL_HANDLE;
		VkPipelineLayout m_PipelineLayout = VK_NULL_HANDLE;

		std::vector<VkDescriptorSetLayout> m_DescriptorLayouts = { };
		std::vector<VkDescriptorPool> m_DescriptorPools = { };

		// Note(Jorben): The first index is the index of the descriptor and the second are VKAPP_MAX_FRAMES_INFLIGHT of sets.
		std::vector<std::vector<VkDescriptorSet>> m_DescriptorSets = { };
	};
}