#pragma once

#include <memory>

#include <vulkan/vulkan.h>

#include <glm/glm.hpp>

#include "Blossom/Renderer/RenderingAPI.hpp"

#include "Blossom/Utils/Utils.hpp"

namespace Blossom
{

	class VulkanRenderPass
	{
	public:
		enum class ColourSpace
		{
			Unorm = 44,
			sRGB = 50
		};

		enum Attachments
		{
			Colour = BIT(0),
			Depth = BIT(1)
		};

	public:
		VulkanRenderPass(const glm::vec2& extent, ColourSpace colourSpace, Attachments attachments);
		virtual ~VulkanRenderPass();

	private:
		void CreateRenderPass(const glm::vec2& extent, ColourSpace colourSpace, Attachments attachments);
		void CreateFrameBuffers(const glm::vec2& extent, ColourSpace colourSpace, Attachments attachments);

	private:
		VkRenderPass m_RenderPass = VK_NULL_HANDLE;

		std::vector<VkFramebuffer> m_SwapChainFramebuffers = { };

	};

}