#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "Blossom/Renderer/RenderingAPI.hpp"

namespace Blossom
{

	class Renderer
	{
	public:
		Renderer() = default;
		virtual ~Renderer() = default;

		static void Init(const APISpecifications& specs);

		static void Clear() { s_Instance->ClearImpl(); }
		static void SetClearColour(const glm::vec4& colour) { s_Instance->SetClearColourImpl(colour); }

		static RenderingAPI GetAPI() { return s_API; }
		static APISpecifications& GetAPISpecs() { return s_APISpecs; }

	private:
		virtual void ClearImpl() = 0;
		virtual void SetClearColourImpl(const glm::vec4& colour) = 0;

	private:
		static std::unique_ptr<Renderer> s_Instance;
		static RenderingAPI s_API;
		static APISpecifications s_APISpecs;
	};

}