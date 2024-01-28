#pragma once

#if defined(BL_EXPOSE_VULKAN)
#include "APIs/Vulkan/Renderer/VulkanRenderer.hpp"

#elif defined(BL_EXPOSE_OPENGL)
#include "APIs/OpenGL/Renderer/OpenGLRenderer.hpp"

#endif