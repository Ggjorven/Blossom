#include "blpch.h"
#include "OpenGLContext.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Blossom/Core/Logging.hpp"

namespace Blossom
{

	static void APIENTRY ErrorCallBack(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		BL_LOG_ERROR("[OpenGL]: type: {0}, id: {1}, severity: {2}, message: {3}", type, id, severity, message);
	}

	OpenGLContext::OpenGLContext(GLFWwindow* handle, bool vsync)
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

		// Enable OpenGL functionality
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(ErrorCallBack, nullptr);

		static uint32_t unusedIDs = 0;
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIDs, true);

		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//
		//glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LESS);
	}

	void OpenGLContext::Destroy()
	{
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
