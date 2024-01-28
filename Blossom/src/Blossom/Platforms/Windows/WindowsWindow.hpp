#pragma once

#if defined(BL_EXPOSE_VULKAN)
#include "APIs/Vulkan/Platforms/Windows/VulkanWindowsWindow.hpp"

#elif defined(BL_EXPOSE_OPENGL)
#include "APIs/OpenGL/Platforms/Windows/OpenGLWindowsWindow.hpp"

#endif