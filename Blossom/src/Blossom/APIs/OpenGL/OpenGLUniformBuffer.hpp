#pragma once

#include "Blossom/Renderer/UniformBuffer.hpp"
#include "Blossom/Renderer/RenderController.hpp"

namespace Blossom
{

	class OpenGLUniformBuffer : public UniformBufferObject
	{
	public:
		OpenGLUniformBuffer(std::shared_ptr<RenderController>& renderController, UniformElement& element, size_t dataSize);
		virtual ~OpenGLUniformBuffer();

		void SetData(void* data, size_t size) override;
		void UploadToController() override;

		void Bind();

	private:
		std::shared_ptr<RenderController> m_RenderController = nullptr;
		UniformElement m_Element = {};
		size_t m_Size = 0;

		uint32_t m_RendererID = 0;
	};

}