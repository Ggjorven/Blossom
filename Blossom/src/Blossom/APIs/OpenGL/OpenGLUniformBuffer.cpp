#include "blpch.h"
#include "OpenGLUniformBuffer.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/OpenGL/OpenGLRenderController.hpp"

#include <GL/glew.h>

namespace Blossom
{

	OpenGLUniformBuffer::OpenGLUniformBuffer(std::shared_ptr<RenderController>& renderController, UniformElement& element, size_t dataSize)
		: m_RenderController(renderController), m_Binding(element.Binding), m_Size(dataSize)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);

		// Allocate appropriate size
		glBufferData(GL_UNIFORM_BUFFER, dataSize, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLUniformBuffer::SetData(void* data, size_t size)
	{
		// TODO(Jorben): Make assert?
		if (size != m_Size)
			BL_LOG_ERROR("Invalid size passed to SetData()");

		glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLUniformBuffer::UploadToController()
	{
		auto rc = OpenGLRenderController::GetController(m_RenderController);

		rc->AddUBO(this);
	}

	void OpenGLUniformBuffer::Bind()
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_RendererID);
		glBindBufferBase(GL_UNIFORM_BUFFER, m_Binding, m_RendererID);
	}

}
