#pragma once

#include <memory>

#include <vulkan/vulkan.h>

#include <glm/glm.hpp>

#include "Blossom/Renderer/RenderingAPI.hpp"

#include "Blossom/Utils/Utils.hpp"

namespace Blossom
{

	enum Attachments
	{
		AttachmentNone = 0,
		ColourAttachment = BIT(0),
		DepthAttachment = BIT(1)
	};

	class VulkanRenderPass
	{
	public:
		enum class ColourSpace
		{
			None = 0,
			Unorm = 44,
			sRGB = 50
		};

	public:
		VulkanRenderPass(const glm::vec2& extent, ColourSpace colourSpace, Attachments attachments);
		VulkanRenderPass(const glm::vec2& extent, ColourSpace colourSpace, int attachments);
		virtual ~VulkanRenderPass();

		void RecreateFrameBuffers();

	private:
		void CreateRenderPass(const glm::vec2& extent, ColourSpace colourSpace, Attachments attachments);
		void CreateFrameBuffers(const glm::vec2& extent, ColourSpace colourSpace, Attachments attachments);

	private:
		ColourSpace m_ColourSpace = ColourSpace::None;
		Attachments m_Attachments = AttachmentNone;

		VkRenderPass m_RenderPass = VK_NULL_HANDLE;
		std::vector<VkFramebuffer> m_SwapChainFramebuffers = { };

	};

}