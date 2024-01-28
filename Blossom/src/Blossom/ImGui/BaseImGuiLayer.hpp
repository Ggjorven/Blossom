#pragma once

#if defined(BL_EXPOSE_VULKAN)
#include "APIs/Vulkan/ImGui/VulkanBaseImGuiLayer.hpp"

#elif defined(BL_EXPOSE_OPENGL)
#include "APIs/OpenGL/ImGui/OpenGLBaseImGuiLayer.hpp"

#endif