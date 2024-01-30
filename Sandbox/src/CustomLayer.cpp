#include "CustomLayer.hpp"

#include <Blossom/Core/Logging.hpp>
#include <Blossom/Renderer/Renderer.hpp>

#include <imgui.h>

void CustomLayer::OnAttach()
{
	Renderer::SetClearColour({ 1.0f, 0.0f, 0.0f, 0.0f });
	BL_LOG_TRACE("Clear Colour: [{0:.2f}, {1:.2f}, {2:.2f}, {3:.2f}]", 1.0f, 0.0f, 0.0f, 0.0f);
}

void CustomLayer::OnDetach()
{
}

void CustomLayer::OnUpdate(float deltaTime)
{
}

void CustomLayer::OnRender()
{
	Renderer::Clear();
}

void CustomLayer::OnImGuiRender()
{
	//ImGui::Begin("Example window");
	//
	//ImGui::End();
}

void CustomLayer::OnEvent(Event& e)
{
}
