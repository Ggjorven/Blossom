#pragma once

#include "Blossom/Renderer/RenderController.hpp"

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

		void Initialize() override;

	private:
		std::shared_ptr<Shader> m_Shader = nullptr;
	};

}