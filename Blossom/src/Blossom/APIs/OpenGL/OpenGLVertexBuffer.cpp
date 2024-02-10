#include "blpch.h"
#include "OpenGLVertexBuffer.hpp"

#include "Blossom/Core/Logging.hpp"

#include <GL/glew.h>

namespace Blossom
{

	static GLenum BufferDataTypeToOpenGLType(BufferDataType type);

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_VertexBufferID);
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(void* vertices, size_t size)
	{
		glCreateVertexArrays(1, &m_VertexArrayID);

		glGenBuffers(1, &m_VertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexBuffer::SetSubData(uint32_t offset, void* data, size_t size)
	{
		// Note(Jorben): Bind before doing this
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_Layout = layout;

		glBindVertexArray(m_VertexArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferID);

		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(element.Location);
			glVertexAttribPointer(element.Location,
				element.GetComponentCount(),
				BufferDataTypeToOpenGLType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
		}
	}

	static GLenum BufferDataTypeToOpenGLType(BufferDataType type)
	{
		switch (type)
		{
		case BufferDataType::Float:    return GL_FLOAT;
		case BufferDataType::Float2:   return GL_FLOAT;
		case BufferDataType::Float3:   return GL_FLOAT;
		case BufferDataType::Float4:   return GL_FLOAT;
		case BufferDataType::Mat3:     return GL_FLOAT;
		case BufferDataType::Mat4:     return GL_FLOAT;
		case BufferDataType::Int:      return GL_INT; // GL_DOUBLE?
		case BufferDataType::Int2:     return GL_INT; // GL_DOUBLE?
		case BufferDataType::Int3:     return GL_INT; // GL_DOUBLE?
		case BufferDataType::Int4:     return GL_INT; // GL_DOUBLE?
		case BufferDataType::Bool:     return GL_BOOL;
		}

		BL_LOG_ERROR("Failed to deduce proper type.");
		return GL_FALSE;
	}

}