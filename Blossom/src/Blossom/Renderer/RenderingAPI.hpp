#pragma once

#include <memory>

#include <glm/glm.hpp>

#include <GL/glew.h>

namespace Blossom
{

	enum class RenderingAPI
	{
		None = -1, OpenGL, Vulkan
	};

	struct APISpecifications
	{
	public:
		enum class MSAASamples
		{
			None = 0, MSAA2 = 2, MSAA4 = 4, MSAA8 = 8, MSAA16 = 16, MSAA32 = 32
		};

		enum class ClearValues
		{
			Colour = 0x00004000,
			Depth = 0x00000100,
			Stencil = 0x8224
		};

	public:
		glm::vec4 ClearColour = { 0.0f, 0.0f, 0.0f, 0.0f };
		MSAASamples MSAA = MSAASamples::None;
		ClearValues ClearValues = ClearValues::Colour;
	};

}