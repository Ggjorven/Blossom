#pragma once

#include "Blossom/Renderer/Image.hpp"
#include "Blossom/Renderer/UniformBuffer.hpp"
#include "Blossom/Renderer/RenderController.hpp"

#include <vulkan/vulkan.h>
#include <vk_mem_alloc.h>

namespace Blossom
{

	class VulkanImage : public Image
	{
	public:
		VulkanImage(std::shared_ptr<RenderController>& controller, UniformElement& element, uint32_t width, uint32_t height);
		VulkanImage(std::shared_ptr<RenderController>& controller, UniformElement& element, const std::filesystem::path& path);
		virtual ~VulkanImage();

		void SetData(void* data, size_t size) override;

		void UploadToController() override;

	private:
		void CreateImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VmaMemoryUsage memoryUsage, VkImage& outImage, VmaAllocation& outAllocation);
		void CopyBufferToImage(VkBuffer& buffer, VkImage& image, uint32_t width, uint32_t height);
		void TransitionImageLayout(VkImage& image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
		void GenerateMipmaps(VkImage& image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);

		VkImageView CreateImageView(VkImage& image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
		VkSampler CreateSampler(uint32_t mipLevels);

	private:
		std::shared_ptr<RenderController> m_Controller = nullptr;
		UniformElement m_Element = {};

		VkImage m_Image = VK_NULL_HANDLE;
		VmaAllocation m_Allocation = VK_NULL_HANDLE;

		VkImageView m_ImageView = VK_NULL_HANDLE;
		VkSampler m_Sampler = VK_NULL_HANDLE;

		uint32_t m_Width = 0, m_Height = 0, m_Miplevels = 0;
	};
}
