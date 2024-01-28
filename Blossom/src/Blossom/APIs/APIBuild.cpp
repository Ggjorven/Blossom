#include "blpch.h"

#if defined(BL_EXPOSE_VULKAN)

#include "Blossom/APIs/Vulkan/Platforms/Windows/VulkanWindowsWindow.cpp"

#include "Blossom/APIs/Vulkan/Renderer/VulkanGraphicsPipelineManager.cpp"
#include "Blossom/APIs/Vulkan/Renderer/VulkanInstanceManager.cpp"
#include "Blossom/APIs/Vulkan/Renderer/VulkanMesh.cpp"
#include "Blossom/APIs/Vulkan/Renderer/VulkanRenderer.cpp"
#include "Blossom/APIs/Vulkan/Renderer/VulkanSwapChainManager.cpp"

#include "Blossom/APIs/Vulkan/Utils/VulkanBufferManager.cpp"

#include "Blossom/APIs/Vulkan/ImGui/VulkanBaseImGuiLayer.cpp"
#include "Blossom/APIs/Vulkan/ImGui/VulkanImGuiBuild.cpp"

#elif defined(BL_EXPOSE_OPENGL)

#include "Blossom/APIs/OpenGL/Platforms/Windows/OpenGLWindowsWindow.cpp"

#include "Blossom/APIs/OpenGL/Renderer/OpenGLRenderer.cpp"

#include "Blossom/APIs/OpenGL/ImGui/OpenGLBaseImGuiLayer.cpp"
#include "Blossom/APIs/OpenGL/ImGui/OpenGLImGuiBuild.cpp"

#else
	#error No API selected.
#endif