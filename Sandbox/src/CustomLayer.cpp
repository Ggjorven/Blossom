#include "CustomLayer.hpp"

#include <GL/glew.h>

#include <imgui.h>

void CustomLayer::OnAttach()
{
}

void CustomLayer::OnDetach()
{
}

void CustomLayer::OnUpdate(float deltaTime)
{
}

void CustomLayer::OnRender()
{
	#if defined(BL_EXPOSE_OPENGL)
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	#elif defined(BL_EXPOSE_VULKAN)

	#endif
}

void CustomLayer::OnImGuiRender()
{
	ImGui::Begin("AA");

	ImGui::End();
}

void CustomLayer::OnEvent(Event& e)
{
}
