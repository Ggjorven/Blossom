#pragma once

#include <memory>
#include <vector>
#include <string>
#include <filesystem>

namespace Blossom
{

	class Shader
	{
	public:
		Shader() = default;
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static std::vector<char> ReadSPIRVFile(const std::filesystem::path& filepath);
		static std::string ReadGLSLFile(const std::filesystem::path& filepath);

		static std::shared_ptr<Shader> Create(const std::vector<char>& vertex, const std::vector<char>& fragment);
		static std::shared_ptr<Shader> Create(const std::string& vertex, const std::string& fragment);
	};

}