#pragma once

#include "Blossom/Renderer/RenderController.hpp"

#include "Blossom/APIs/OpenGL/OpenGLUniformBuffer.hpp"
#include "Blossom/APIs/OpenGL/OpenGLImage.hpp"

namespace Blossom
{

	class OpenGLRenderController : public RenderController
	{
	public:
		OpenGLRenderController() = default;
		virtual ~OpenGLRenderController() = default;

		void Use() override;

		void SetShader(std::shared_ptr<Shader>& shader) override;
		void SetBufferLayout(BufferLayout& layout) override;
		void SetUniformLayout(UniformLayout& layout) override;

		void Initialize() override;

		// TODO(Jorben): Add a way to remove UBO's?
		void AddUBO(OpenGLUniformBuffer* buffer);
		void AddImage(OpenGLImage* image);

		static std::shared_ptr<OpenGLRenderController> GetController(std::shared_ptr<RenderController>& renderController);

	private:
		std::shared_ptr<Shader> m_Shader = nullptr;

		std::vector<OpenGLUniformBuffer*> m_UBOs = { };
		std::vector<OpenGLImage*> m_Images = { };
	};

}