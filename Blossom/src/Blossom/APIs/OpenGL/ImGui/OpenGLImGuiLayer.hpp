#pragma once

#include "Blossom/ImGui/BaseImGuiLayer.hpp"

namespace Blossom
{

	class OpenGLImGuiLayer : public BaseImGuiLayer
	{
	public:
		OpenGLImGuiLayer() = default;
		virtual ~OpenGLImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;

		void Begin() override;
		void End() override;
	};

}