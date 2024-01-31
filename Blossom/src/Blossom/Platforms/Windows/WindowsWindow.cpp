#include "blpch.h"
#include "WindowsWindow.hpp"

#include "Blossom/Core/Events.hpp"
#include "Blossom/Core/Logging.hpp"

#include "Blossom/Renderer/Renderer.hpp"

namespace Blossom
{

	bool WindowsWindow::s_GLFWinitialized = false;
	uint32_t WindowsWindow::s_Instances = 0u;

	static void ConfigureWindowPreferences();

	WindowsWindow::WindowsWindow(const WindowProperties properties)
	{
		if (Init(properties))
			BL_LOG_ERROR("{0}", "WindowsWindow failed to initialize.");
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
	}

	void WindowsWindow::OnRender()
	{
		m_GraphicsContext->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		// TODO(Jorben): Renderer recreate (for vulkan)
		m_Data.Vsync = enabled;
	}

	void WindowsWindow::SetTitle(const std::string& title)
	{
		glfwSetWindowTitle(m_Window, title.c_str());
	}
	
	bool WindowsWindow::Init(WindowProperties properties)
	{
		if (!s_GLFWinitialized)
		{
			int succes = glfwInit();
			if (!succes)
			{
				BL_LOG_ERROR("glfwInit() failed");
				return true;
			}
			s_GLFWinitialized = true;
			glfwSetErrorCallback(ErrorCallBack);
		}
		m_Data.Vsync = properties.VSync;

		ConfigureWindowPreferences();
		m_Window = glfwCreateWindow((int)properties.Width, (int)properties.Height, properties.Name.c_str(), nullptr, nullptr);
		s_Instances++;

		m_GraphicsContext = GraphicsContext::Create(m_Window);
		m_GraphicsContext->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data); //So we can access/get to the data in lambda functions
		if (properties.CustomPos) glfwSetWindowPos(m_Window, properties.X, properties.Y);

		//Event system
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.CallBack(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.CallBack(event);
			});


		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.CallBack(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.CallBack(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.CallBack(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.CallBack(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.CallBack(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.CallBack(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.CallBack(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.CallBack(event);
			});


		return false;
	}

	void WindowsWindow::Shutdown()
	{
		m_GraphicsContext->Destroy();

		glfwDestroyWindow(m_Window);
		s_Instances--;

		if (s_Instances == 0)
			glfwTerminate();
	}

	void WindowsWindow::ErrorCallBack(int errorCode, const char* description)
	{
		BL_LOG_ERROR("[GLFW]: ({0}), {1}", errorCode, description);
	}

	void ConfigureWindowPreferences()
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::OpenGL:
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
			break;
		case RenderingAPI::Vulkan:
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			break;

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}
	}

}