#pragma once

#include <queue>

#include "Blossom/Renderer/Renderer.hpp"
	
namespace Blossom
{

	class OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer() = default;
		virtual ~OpenGLRenderer() = default;

	private:
		void WaitImpl() override;

		void ClearImpl() override;
		void SetClearColourImpl(const glm::vec4& colour) override;

		void DrawIndexedImpl(std::shared_ptr<IndexBuffer>& indexBuffer) override;

		void OnResizeImpl(uint32_t width, uint32_t height) override;

		void AddToQueueImpl(RenderFunction function) override;
		void AddToUIQueueImpl(UIFunction function) override;

		void DisplayImpl() override;

	private:
		std::queue<RenderFunction> m_RenderFunctions = { };
	};

}