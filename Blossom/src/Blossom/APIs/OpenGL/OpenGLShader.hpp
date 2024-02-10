#pragma once

#include "Blossom/Renderer/Shader.hpp"

#include <unordered_map>

namespace Blossom
{

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::vector<char>& vertex, const std::vector<char>& fragment);
		OpenGLShader(const std::string& vertexSource, const std::string fragmentSource);
		virtual ~OpenGLShader();

		void Bind() const override;
		void UnBind() const override;

	private:
		uint32_t Create(const std::string& vertexSource, const std::string& fragmentSource);
		uint32_t Compile(uint32_t type, const std::string& data);

	private:
		uint32_t m_RendererID = 0;

		std::unordered_map<uint32_t, int32_t> m_IntermediateShaderIDs;
	};

}