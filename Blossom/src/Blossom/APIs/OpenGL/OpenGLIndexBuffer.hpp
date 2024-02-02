#pragma once

#include "Blossom/Renderer/IndexBuffer.hpp"

namespace Blossom
{

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		void Bind() const override;
		void UnBind() const override;

		uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_Count = 0;
	};

}