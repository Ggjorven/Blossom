#include "blpch.h"
#include "OpenGLImage.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/APIs/OpenGL/OpenGLRenderController.hpp"

#include <stb_image.h>

namespace Blossom
{

	OpenGLImage::OpenGLImage(std::shared_ptr<RenderController>& controller, UniformElement& element, uint32_t width, uint32_t height)
		: m_Controller(controller), m_Element(element), m_Width(width), m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLImage::OpenGLImage(std::shared_ptr<RenderController>& controller, UniformElement& element, const std::filesystem::path& path)
		: m_Controller(controller), m_Element(element)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);

		stbi_uc* data = stbi_load(path.string().c_str(), &width, &height, &channels, 0);
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		switch (channels)
		{
		case 4:
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
			break;
		case 3:
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
			break;
		default:
			BL_LOG_ERROR("Format not supported!");
			stbi_image_free((void*)data);
			return;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free((void*)data);

		//glGenerateMipmap(GL_TEXTURE_2D);
	}

	void OpenGLImage::SetData(void* data, size_t size)
	{
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}

	void OpenGLImage::UploadToController()
	{
		auto rc = OpenGLRenderController::GetController(m_Controller);

		rc->AddImage(this);
	}

	void OpenGLImage::Bind()
	{
		glBindTextureUnit(m_Element.Binding, m_RendererID);
	}

}