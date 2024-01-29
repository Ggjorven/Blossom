#pragma once

#include "Blossom/ImGui/BaseImGuiLayer.hpp"

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
	};

}