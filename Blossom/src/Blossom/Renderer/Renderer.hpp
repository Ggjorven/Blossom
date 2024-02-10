#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Blossom/Renderer/RenderingAPI.hpp"
#include "Blossom/Renderer/RenderController.hpp"

namespace Blossom
{

	class Application;
	class VertexBuffer;
	class IndexBuffer;

	typedef std::function<void()> RenderFunction;
	typedef std::function<void()> UIFunction;

	class Renderer
	{
	public:
		Renderer() = default;
		virtual ~Renderer() = default;

		static void Init(const APISpecifications& specs);
		static void Destroy();

		static void Wait() { s_Instance->WaitImpl(); }

		static void Clear() { s_Instance->ClearImpl(); }
		static void SetClearColour(const glm::vec4& colour) { s_Instance->SetClearColourImpl(colour); }

		// Note(Jorben): Make sure you have a RenderController bound
		static void DrawIndexed(std::shared_ptr<IndexBuffer>& indexBuffer) { s_Instance->DrawIndexedImpl(indexBuffer); }

		static void AddToQueue(RenderFunction function) { s_Instance->AddToQueueImpl(function); }
		static void AddToUIQueue(UIFunction function) { s_Instance->AddToUIQueueImpl(function); }

		static RenderingAPI GetAPI() { return s_API; }
		static APISpecifications& GetAPISpecs() { return s_APISpecs; }

		static void OnResize(uint32_t width, uint32_t height) { s_Instance->OnResizeImpl(width, height); }

	private:
		virtual void WaitImpl() = 0;

		virtual void ClearImpl() = 0;
		virtual void SetClearColourImpl(const glm::vec4& colour) = 0;

		virtual void DrawIndexedImpl(std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual void OnResizeImpl(uint32_t width, uint32_t height) = 0;

		virtual void AddToQueueImpl(RenderFunction function) = 0;
		virtual void AddToUIQueueImpl(UIFunction function) = 0;

		static void Display() { s_Instance->DisplayImpl(); }
		virtual void DisplayImpl() = 0;

	private:
		static Renderer* s_Instance;
		static constexpr const RenderingAPI s_API = RenderingAPI::Vulkan; // Note(Jorben): This is where the API is selected.
		static APISpecifications s_APISpecs;

		friend class Application;
	};

}