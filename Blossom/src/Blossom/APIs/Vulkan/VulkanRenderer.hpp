#pragma once

#include "Blossom/Renderer/Renderer.hpp"

namespace Blossom
{

	class VulkanRenderer : public Renderer
	{
	public:
		VulkanRenderer() = default;
		virtual ~VulkanRenderer() = default;

	private:
		void ClearImpl() override;
		void SetClearColourImpl(const glm::vec4& colour) override;

		void UseControllerImpl(const RenderController& controller) override;
	};

}