#include "blpch.h"
#include "VulkanShader.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/Vulkan/VulkanManager.hpp"

namespace Blossom
{

	VulkanShader::VulkanShader(const std::vector<char>& vertex, const std::vector<char>& fragment)
	{
		m_VertexShader = CreateShaderModule(vertex);
		m_FragmentShader = CreateShaderModule(fragment);
	}

	VulkanShader::~VulkanShader()
	{
		auto& info = VulkanManager::GetDeviceInfo();

		vkDestroyShaderModule(info.Device, m_FragmentShader, nullptr);
		vkDestroyShaderModule(info.Device, m_VertexShader, nullptr);
	}

	void VulkanShader::Bind() const
	{
		// Note(Jorben): This function is irrelevant for Vulkan
	}

	void VulkanShader::UnBind() const
	{
		// Note(Jorben): This function is irrelevant for Vulkan
	}

	std::shared_ptr<VulkanShader> VulkanShader::GetShader(std::shared_ptr<Shader>& shader)
	{
		std::shared_ptr<VulkanShader> vulkanShaderPtr = std::dynamic_pointer_cast<VulkanShader>(shader);

		if (!vulkanShaderPtr)
			BL_LOG_ERROR("Failed to convert std::shared_ptr<Shader> to a std::shared_ptr<VulkanShader>");

		return vulkanShaderPtr;
	}

	VkShaderModule VulkanShader::CreateShaderModule(const std::vector<char>& data)
	{
		auto& info = VulkanManager::GetDeviceInfo();

		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = data.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(data.data());

		VkShaderModule shaderModule = {};
		if (vkCreateShaderModule(info.Device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
			BL_LOG_ERROR("Failed to create shader module!");

		return shaderModule;
	}

}