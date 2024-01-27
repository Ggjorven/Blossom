#include "blpch.h"
#include "Window.hpp"

#include "Blossom/Platforms/Windows/WindowsWindow.hpp"

namespace VkApp
{

	std::unique_ptr<Window> Window::Create(const WindowProperties properties)
	{
		#ifdef BL_PLATFORM_WINDOWS
		return std::make_unique<WindowsWindow>(properties);
		#endif

		// TODO(Jorben): Add all the platforms
	}

}