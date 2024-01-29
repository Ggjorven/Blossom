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

	};

}