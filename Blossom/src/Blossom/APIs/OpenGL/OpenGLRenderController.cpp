#include "blpch.h"
#include "OpenGLRenderController.hpp"

namespace Blossom
{

	void OpenGLRenderController::Use()
	{
		m_Shader->Bind();
	}

	void OpenGLRenderController::SetShader(std::shared_ptr<Shader>& shader)
	{
		m_Shader = shader;
	}

	void OpenGLRenderController::SetBufferLayout(BufferLayout& layout)
	{
		// Note(Jorben): This function is irrelevant for OpenGL
	}

	void OpenGLRenderController::SetUniformLayout(UniformLayout& layout)
	{
		// !TODO(Jorben): Implement
	}

	void OpenGLRenderController::Initialize()
	{
		// Note(Jorben): This function is irrelevant for OpenGL
	}

}