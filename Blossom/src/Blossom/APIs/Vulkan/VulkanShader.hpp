#pragma once

#include "Blossom/Renderer/Shader.hpp"

#include <vulkan/vulkan.h>

namespace Blossom
{

	class VulkanShader : public Shader
	{
	public:
		VulkanShader(const std::vector<char>& vertex, const std::vector<char>& fragment);
		//VulkanShader(const std::string& vertex, const std::string& fragment); // TODO
		virtual ~VulkanShader();

		void Bind() const;
		void UnBind() const;

		VkShaderModule& GetVertexShader() { return m_VertexShader; }
		VkShaderModule& GetFragmentShader() { return m_FragmentShader; }

		static std::shared_ptr<VulkanShader> GetShader(std::shared_ptr<Shader>& shader);

	private:
		VkShaderModule CreateShaderModule(const std::vector<char>& data);

	private:
		VkShaderModule m_VertexShader = VK_NULL_HANDLE;
		VkShaderModule m_FragmentShader = VK_NULL_HANDLE;
	};

}