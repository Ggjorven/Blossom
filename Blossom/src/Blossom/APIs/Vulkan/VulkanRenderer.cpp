#include "blpch.h"
#include "VulkanRenderer.hpp"

#include <vulkan/vulkan.h>

namespace Blossom
{

	void VulkanRenderer::ClearImpl()
	{
		// Note(Jorben): This function is kinda redundant for vulkan so it is empty
	}

	void VulkanRenderer::SetClearColourImpl(const glm::vec4& colour)
	{
		Renderer::GetAPISpecs().ClearColour = colour;
	}

	void VulkanRenderer::UseControllerImpl(const RenderController& controller)
	{
	}

}