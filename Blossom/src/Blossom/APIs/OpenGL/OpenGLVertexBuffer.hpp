#pragma once

#include "Blossom/Renderer/VertexBuffer.hpp"

namespace Blossom
{

	// TODO(Jorben): Implement vertexarray
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* vertices, size_t size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void UnBind() const override;

		void SetSubData(uint32_t offset, void* data, size_t size);

		BufferLayout& GetLayout() override { return m_Layout; }
		void SetLayout(const BufferLayout& layout) override;

	private:
		uint32_t m_VertexArrayID = 0;
		uint32_t m_VertexBufferID = 0;

		BufferLayout m_Layout = {};
	};

}