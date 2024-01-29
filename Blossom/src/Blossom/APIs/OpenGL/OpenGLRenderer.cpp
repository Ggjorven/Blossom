#include "blpch.h"
#include "OpenGLRenderer.hpp"

#include <GL/glew.h>

namespace Blossom
{

	void OpenGLRenderer::ClearImpl()
	{
		glClear((unsigned int)Renderer::GetAPISpecs().ClearValues);
	}

	void OpenGLRenderer::SetClearColourImpl(const glm::vec4& colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);
		Renderer::GetAPISpecs().ClearColour = colour;
	}

}