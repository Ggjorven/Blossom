#pragma once

#include <memory>

#include "Blossom/Renderer/Shader.hpp"
#include "Blossom/Renderer/VertexBuffer.hpp"

#include "Blossom/Renderer/UniformBuffer.hpp"

namespace Blossom
{

	class RenderController
	{
	public:
		RenderController() = default;
		virtual ~RenderController() = default;

		virtual void Use() = 0;

		virtual void SetShader(std::shared_ptr<Shader>& shader) = 0;
		virtual void SetBufferLayout(BufferLayout& layout) = 0;
		virtual void SetUniformLayout(UniformLayout& layout) = 0;

		virtual void Initialize() = 0;

		static std::shared_ptr<RenderController> Create();
	};

}