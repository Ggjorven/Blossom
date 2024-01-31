#pragma once

#include <memory>

namespace Blossom
{

	class GraphicsContext
	{
	public:
		GraphicsContext() = default;
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void Destroy() = 0;

		virtual void SwapBuffers() = 0;

		static std::unique_ptr<GraphicsContext> Create(void* window, bool vsync = false);
	};

}