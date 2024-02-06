#include "blpch.h"
#include "OpenGLRenderController.hpp"

namespace Blossom
{

	void OpenGLRenderController::Use()
	{
		m_Shader->Bind();

		for (auto& ubo : m_UBOs)
		{
			if (ubo) // Note(Jorben): A check if the pointer is valid, since there is no way to remove UBO from the list atm
				ubo->Bind();
		}
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

	void OpenGLRenderController::AddUBO(OpenGLUniformBuffer* buffer)
	{
		m_UBOs.push_back(buffer);
	}

	std::shared_ptr<OpenGLRenderController> OpenGLRenderController::GetController(std::shared_ptr<RenderController>& renderController)
	{
		std::shared_ptr<OpenGLRenderController> openglRCPtr = std::dynamic_pointer_cast<OpenGLRenderController>(renderController);

		if (!openglRCPtr)
			BL_LOG_ERROR("Failed to convert std::shared_ptr<RenderController> to a std::shared_ptr<OpenGLRenderController>");

		return openglRCPtr;
	}

}