#include "blpch.h"
#include "OpenGLShader.hpp"

#include "Blossom/Core/Logging.hpp"

#include <GL/glew.h>

namespace Blossom
{

	OpenGLShader::OpenGLShader(const std::vector<char>& vertex, const std::vector<char>& fragment)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderBinary(1, &vertexShader, GL_SHADER_BINARY_FORMAT_SPIR_V, vertex.data(), (int)vertex.size());
		glSpecializeShader(vertexShader, "main", 0, nullptr, nullptr);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderBinary(1, &fragmentShader, GL_SHADER_BINARY_FORMAT_SPIR_V, fragment.data(), (int)fragment.size());
		glSpecializeShader(fragmentShader, "main", 0, nullptr, nullptr);

		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		glLinkProgram(m_RendererID);

		// Check for linking errors
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			std::string errorMsg(infoLog.begin(), infoLog.end());
			BL_LOG_ERROR("OpenGL linking error: {0}", errorMsg);
		}

		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string fragmentSource)
	{
		m_RendererID = Create(vertexSource, fragmentSource);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	uint32_t OpenGLShader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		GLuint program = glCreateProgram();

		GLuint vertexShader = Compile(GL_VERTEX_SHADER, vertexSource);
		GLuint fragmentShader = Compile(GL_FRAGMENT_SHADER, fragmentSource);

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		glValidateProgram(program);

		//Check for linking failure
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint length = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);

			std::vector<GLchar> infoLog(length);
			glGetProgramInfoLog(program, length, &length, &infoLog[0]);

			glDeleteProgram(program);

			BL_LOG_ERROR("[OpenGL] Error: Shader linking failure... {0}", infoLog.data());

			return 0;
		}

		//Cleanup
		glDeleteShader(m_IntermediateShaderIDs[GL_VERTEX_SHADER]);
		glDeleteShader(m_IntermediateShaderIDs[GL_FRAGMENT_SHADER]);

		return program;
	}

	uint32_t OpenGLShader::Compile(uint32_t type, const std::string& data)
	{
		GLuint id = glCreateShader(type);

		const char* source = data.c_str();
		glShaderSource(id, 1, &source, nullptr);
		glCompileShader(id);

		//Check for compilation failure
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

			std::vector<GLchar> infoLog(length);
			glGetShaderInfoLog(id, length, &length, &infoLog[0]);

			BL_LOG_ERROR("[OpenGL] Error: Shader compilation failure... {0}", infoLog.data());

			glDeleteShader(id);
			return 0;
		}

		m_IntermediateShaderIDs[type] = id;
		return id;
	}

}