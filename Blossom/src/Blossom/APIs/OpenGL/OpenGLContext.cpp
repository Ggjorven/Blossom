#include "blpch.h"
#include "OpenGLContext.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Blossom/Core/Logging.hpp"

namespace Blossom
{

	OpenGLContext::OpenGLContext(GLFWwindow* handle)
		: m_WindowHandle(handle)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		
		if (glewInit() != GLEW_OK)
		{
			BL_LOG_FATAL("Failed to initialize OpenGL context.");
			return;
		}
	}

	void OpenGLContext::Destroy()
	{
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
