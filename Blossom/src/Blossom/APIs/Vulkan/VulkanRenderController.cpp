#include "blpch.h"
#include "VulkanRenderController.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/Vulkan/VulkanContext.hpp"
#include "Blossom/APIs/Vulkan/VulkanManager.hpp"
#include "Blossom/APIs/Vulkan/VulkanRenderer.hpp"

namespace Blossom
{

	static VkFormat BufferDataTypeToVulkanType(BufferDataType type);

	VulkanRenderController::VulkanRenderController()
	{
	}

	VulkanRenderController::~VulkanRenderController()
	{
		auto& info = VulkanManager::GetDeviceInfo();

		vkDestroyPipeline(info.Device, m_GraphicsPipeline, nullptr);
		vkDestroyPipelineLayout(info.Device, m_PipelineLayout, nullptr);

		for (auto& pool : m_DescriptorPools)
		{
			vkDestroyDescriptorPool(info.Device, pool, nullptr);
		}

		for (auto& layout : m_DescriptorLayouts)
		{
			vkDestroyDescriptorSetLayout(info.Device, layout, nullptr);
		}
	}

	void VulkanRenderController::Use()
	{
		auto& resourceInfo = VulkanManager::GetResourceInfo();

		vkCmdBindPipeline(resourceInfo.CommandBuffers[VulkanRenderer::GetCurrentFrame()], VK_PIPELINE_BIND_POINT_GRAPHICS, m_GraphicsPipeline);
	}

	void VulkanRenderController::SetShader(std::shared_ptr<Shader>& shader)
	{
		m_Shader = VulkanShader::GetShader(shader);
	}

	void VulkanRenderController::SetBufferLayout(BufferLayout& layout)
	{
		m_BufferLayout = layout;
	}

	void VulkanRenderController::Initialize()
	{
		CreateDescriptorSetLayout();
		CreateGraphicsPipeline();
		CreateDescriptorPool();
		CreateDescriptorSets();
	}

	void VulkanRenderController::CreateDescriptorSetLayout()
	{
		// TODO(Jorben): Implement
	}

	void VulkanRenderController::CreateGraphicsPipeline()
	{
		VkShaderModule vertShaderModule = m_Shader->GetVertexShader();
		VkShaderModule fragShaderModule = m_Shader->GetFragmentShader();

		// Vertex shader info
		VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
		vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageInfo.module = vertShaderModule;
		vertShaderStageInfo.pName = "main";

		// Fragment shader info
		VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
		fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragShaderStageInfo.module = fragShaderModule;
		fragShaderStageInfo.pName = "main";

		// PipelineShader info
		VkPipelineShaderStageCreateInfo shaderStages[2] = { vertShaderStageInfo, fragShaderStageInfo };

		auto bindingDescription = GetBindingDescription();
		auto attributeDescriptions = GetAttributeDescriptions();

		VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 1;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
		vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

		VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkPipelineViewportStateCreateInfo viewportState = {};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.scissorCount = 1;

		VkPipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_FRONT_BIT; // Change to VK_CULL_MODE_BACK_BIT?
		rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;

		VkPipelineMultisampleStateCreateInfo multisampling = {};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE; // Note(Jorben): Set true for transparancy

		VkPipelineColorBlendStateCreateInfo colorBlending = {};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		VkPipelineDepthStencilStateCreateInfo depthStencil = {};
		depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencil.depthTestEnable = VK_TRUE;
		depthStencil.depthWriteEnable = VK_TRUE;
		depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
		depthStencil.depthBoundsTestEnable = VK_FALSE;
		depthStencil.minDepthBounds = 0.0f; // Optional
		depthStencil.maxDepthBounds = 1.0f; // Optional
		depthStencil.stencilTestEnable = VK_FALSE;
		depthStencil.front = {}; // Optional
		depthStencil.back = {}; // Optional

		std::vector<VkDynamicState> dynamicStates = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};

		VkPipelineDynamicStateCreateInfo dynamicState = {};
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
		dynamicState.pDynamicStates = dynamicStates.data();

		VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(m_DescriptorLayouts.size());
		pipelineLayoutInfo.pSetLayouts = m_DescriptorLayouts.data();

		auto& info = VulkanManager::GetDeviceInfo();

		if (vkCreatePipelineLayout(info.Device, &pipelineLayoutInfo, nullptr, &m_PipelineLayout) != VK_SUCCESS)
			BL_LOG_ERROR("Failed to create pipeline layout!");

		// Create the actual graphics pipeline (where we actually use the shaders and other info)
		VkGraphicsPipelineCreateInfo pipelineInfo = {};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = &depthStencil;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = &dynamicState;
		pipelineInfo.layout = m_PipelineLayout;
		pipelineInfo.renderPass = VulkanContext::Get()->GetResources()->GetRenderPasses()[0]->GetVkRenderPass(); // Note(Jorben): Maybe change this with multiple renderpasses maybe
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
		pipelineInfo.basePipelineIndex = -1; // Optional

		if (vkCreateGraphicsPipelines(info.Device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_GraphicsPipeline) != VK_SUCCESS)
			BL_LOG_ERROR("Failed to create graphics pipeline!");
	}

	void VulkanRenderController::CreateDescriptorPool()
	{
		// TODO(Jorben): Implement
	}

	void VulkanRenderController::CreateDescriptorSets()
	{
		// TODO(Jorben): Implement
	}

	VkVertexInputBindingDescription VulkanRenderController::GetBindingDescription()
	{
		VkVertexInputBindingDescription description = {};
		description.binding = 0;
		description.stride = m_BufferLayout.GetStride();
		description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return description;
	}

	std::vector<VkVertexInputAttributeDescription> VulkanRenderController::GetAttributeDescriptions()
	{
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions = {};
		attributeDescriptions.resize(m_BufferLayout.GetElements().size());

		auto& elements = m_BufferLayout.GetElements();
		for (size_t i = 0; i < elements.size(); i++)
		{
			attributeDescriptions[i].binding = 0;
			attributeDescriptions[i].location = elements[i].Location;
			attributeDescriptions[i].format = BufferDataTypeToVulkanType(elements[i].Type);
			attributeDescriptions[i].offset = (uint32_t)elements[i].Offset;
		}

		return attributeDescriptions;
	}

	static VkFormat BufferDataTypeToVulkanType(BufferDataType type)
	{
		switch (type)
		{
		case BufferDataType::Float:   return VK_FORMAT_R32_SFLOAT;
		case BufferDataType::Float2:  return VK_FORMAT_R32G32_SFLOAT;
		case BufferDataType::Float3:  return VK_FORMAT_R32G32B32_SFLOAT;
		case BufferDataType::Float4:  return VK_FORMAT_R32G32B32A32_SFLOAT;
		case BufferDataType::Mat3:    return VK_FORMAT_UNDEFINED;		// TODO(Jorben): Implement these
		case BufferDataType::Mat4:    return VK_FORMAT_UNDEFINED;		// TODO(Jorben): Implement these
		case BufferDataType::Int:     return VK_FORMAT_UNDEFINED;		// TODO(Jorben): Implement these
		case BufferDataType::Int2:    return VK_FORMAT_UNDEFINED;		// TODO(Jorben): Implement these
		case BufferDataType::Int3:    return VK_FORMAT_UNDEFINED;		// TODO(Jorben): Implement these
		case BufferDataType::Int4:    return VK_FORMAT_UNDEFINED;		// TODO(Jorben): Implement these
		case BufferDataType::Bool:    return VK_FORMAT_UNDEFINED;		// TODO(Jorben): Implement these
		}

		return VK_FORMAT_UNDEFINED;
	}
}