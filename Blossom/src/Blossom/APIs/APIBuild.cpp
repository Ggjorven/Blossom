#include "blpch.h"

#if defined(BL_EXPOSE_VULKAN)

#include "Blossom/APIs/Vulkan/ImGui/VulkanBaseImGuiLayer.cpp"
#include "Blossom/APIs/Vulkan/ImGui/VulkanImGuiBuild.cpp"

#include "Blossom/APIs/Vulkan/Platforms/VulkanWindowsWindow.cpp"

#include "Blossom/APIs/Vulkan/Renderer/VulkanGraphicsPipelineManager.cpp"
#include "Blossom/APIs/Vulkan/Renderer/VulkanInstanceManager.cpp"
#include "Blossom/APIs/Vulkan/Renderer/VulkanMesh.cpp"
#include "Blossom/APIs/Vulkan/Renderer/VulkanRenderer.cpp"
#include "Blossom/APIs/Vulkan/Renderer/VulkanSwapChainManager.cpp"

#include "Blossom/APIs/Vulkan/Utils/VulkanBufferManager.cpp"

#elif defined(BL_EXPOSE_OPENGL)


#else
	#error No API selected.
#endif