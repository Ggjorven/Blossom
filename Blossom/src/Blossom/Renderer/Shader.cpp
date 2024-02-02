#include "blpch.h"
#include "Shader.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/Renderer/Renderer.hpp"

#include "Blossom/APIs/OpenGL/OpenGLShader.hpp"
//#include "Blossom/APIs/Vulkan/VulkanShader.hpp"

namespace Blossom
{

	std::vector<uint32_t> Shader::ReadSPIRVFile(const std::filesystem::path& filepath)
	{
		std::ifstream file(filepath, std::ios::ate | std::ios::binary);

		if (!file.is_open() || !file.good())
		{
			BL_LOG_ERROR("Failed to open file!");
			return std::vector<uint32_t>();
		}

		size_t fileSize = (size_t)file.tellg();
		size_t bufferSize = (fileSize + sizeof(uint32_t) - 1) / sizeof(uint32_t);

		std::vector<uint32_t> buffer(bufferSize);
		file.seekg(0);
		file.read(reinterpret_cast<char*>(buffer.data()), fileSize);

		file.close();
		return buffer;
	}

	std::string Shader::ReadGLSLFile(const std::filesystem::path& filepath)
	{
		std::ifstream file(filepath);

		if (!file.is_open() || !file.good())
		{
			BL_LOG_ERROR("Failed to open file!");
			return std::string();
		}

		std::string line;
		std::stringstream ss;

		while (std::getline(file, line))
			ss << line << "\n";

		return ss.str();
	}

	std::shared_ptr<Shader> Shader::Create(const std::vector<uint32_t>& vertex, const std::vector<uint32_t>& fragment)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::OpenGL:
			return nullptr;
		case RenderingAPI::Vulkan:
			return nullptr;

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}

		return nullptr;
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& vertex, const std::string& fragment)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::OpenGL:
			return std::make_shared<OpenGLShader>(vertex, fragment);
		case RenderingAPI::Vulkan:
			return nullptr;

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}

		return nullptr;
	}

}