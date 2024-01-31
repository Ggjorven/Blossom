#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Blossom/Renderer/RenderingAPI.hpp"
#include "Blossom/Renderer/RenderController.hpp"

namespace Blossom
{

	class Renderer
	{
	public:
		Renderer() = default;
		virtual ~Renderer() = default;

		static void Init(const APISpecifications& specs);
		static void Destroy();

		static void Clear() { s_Instance->ClearImpl(); }
		static void SetClearColour(const glm::vec4& colour) { s_Instance->SetClearColourImpl(colour); }

		static void UseController(const RenderController& controller) { s_Instance->UseControllerImpl(controller); }

		static RenderingAPI GetAPI() { return s_API; }
		static APISpecifications& GetAPISpecs() { return s_APISpecs; }

		static void OnResize(uint32_t width, uint32_t height) { s_Instance->OnResizeImpl(width, height); }

	private:
		virtual void ClearImpl() = 0;
		virtual void SetClearColourImpl(const glm::vec4& colour) = 0;

		virtual void UseControllerImpl(const RenderController& controller) = 0;

		virtual void OnResizeImpl(uint32_t width, uint32_t height) = 0;

	private:
		static Renderer* s_Instance;
		static RenderingAPI s_API;
		static APISpecifications s_APISpecs;

		static RenderController s_BoundController;
	};

}