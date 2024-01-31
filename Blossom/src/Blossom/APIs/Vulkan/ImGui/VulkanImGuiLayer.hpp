#pragma once

#include "Blossom/ImGui/BaseImGuiLayer.hpp"

#include <vulkan/vulkan.h>

namespace Blossom
{

	class VulkanImGuiLayer : public BaseImGuiLayer
	{
	public:
		VulkanImGuiLayer() = default;
		virtual ~VulkanImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;

		void Begin() override;
		void End() override;

	private:
		void CreateDescriptorPool();

	private:
		VkDescriptorPool m_DescriptorPool = VK_NULL_HANDLE;
	};

}