#pragma once

#include "Blossom/Renderer/Renderer.hpp"
	
namespace Blossom
{

	class OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer() = default;
		virtual ~OpenGLRenderer() = default;

	private:
		void ClearImpl() override;
		void SetClearColourImpl(const glm::vec4& colour) override;

		void UseControllerImpl(const RenderController& controller) override;

		void OnResizeImpl(uint32_t width, uint32_t height) override {}
	};

}