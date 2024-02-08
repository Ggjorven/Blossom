#pragma once

#include "Blossom/Renderer/Image.hpp"

#include "Blossom/Renderer/UniformBuffer.hpp"
#include "Blossom/Renderer/RenderController.hpp"

#include <GL/glew.h>

namespace Blossom
{

	class OpenGLImage : public Image
	{
	public:
		OpenGLImage(std::shared_ptr<RenderController>& controller, UniformElement& element, uint32_t width, uint32_t height);
		OpenGLImage(std::shared_ptr<RenderController>& controller, UniformElement& element, const std::filesystem::path& path);

		void SetData(void* data, size_t size) override;

		void UploadToController() override;

		void Bind();

	private:
		std::shared_ptr<RenderController> m_Controller = nullptr;
		UniformElement m_Element = {};

		uint32_t m_Width = 0, m_Height = 0;
		uint32_t m_RendererID = 0;

		GLenum m_InternalFormat = 0, m_DataFormat = 0;
	};

}