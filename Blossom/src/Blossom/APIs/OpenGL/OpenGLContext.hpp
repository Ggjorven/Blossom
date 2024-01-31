#pragma once

#include "Blossom/Renderer/GraphicsContext.hpp"

#include <GLFW/glfw3.h>

namespace Blossom
{

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* handle, bool vsync = false);
		virtual ~OpenGLContext() = default;

		void Init() override;
		void Destroy() override;

		void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle = nullptr;
	};
}