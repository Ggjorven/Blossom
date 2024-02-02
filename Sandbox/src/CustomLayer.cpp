#include "CustomLayer.hpp"

#include <Blossom/Core/Logging.hpp>
#include <Blossom/Renderer/Renderer.hpp>

#include <imgui.h>

void CustomLayer::OnAttach()
{
	Renderer::SetClearColour({ 0.0f, 0.0f, 0.0f, 0.0f });

	float squareVertices[6 * 4] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f
	};

	uint32_t squareIndices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	m_VertexBuffer = VertexBuffer::Create((void*)squareVertices, sizeof(squareVertices));
	m_VertexBuffer->SetLayout({
		BufferElement(BufferDataType::Float3, 0, "a_Position", false),
		BufferElement(BufferDataType::Float3, 1, "a_Colour", false)
	});

	m_IndexBuffer = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

	std::string vertex = R"(
	#version 460 core

	layout(location = 0) in vec3 a_Position;
	layout(location = 1) in vec3 a_Colour;

	out vec3 v_Colour;

	void main()
	{
		gl_Position = vec4(a_Position, 1.0);
		v_Colour = a_Colour;
	}
)";

	std::string fragment = R"(
	#version 460 core

	layout(location = 0) out vec4 colour;

	in vec3 v_Colour;

	void main()
	{
		colour = vec4(v_Colour, 1.0);
	}
)";

	m_Shader = Shader::Create(vertex, fragment);
}

void CustomLayer::OnDetach()
{
}

void CustomLayer::OnUpdate(float deltaTime)
{
	m_Timer += deltaTime;
}

void CustomLayer::OnRender()
{
	Renderer::Clear();

	m_Shader->Bind();

	m_VertexBuffer->Bind();
	m_IndexBuffer->Bind();

	Renderer::DrawIndexed(m_IndexBuffer);

	m_IndexBuffer->UnBind();
	m_VertexBuffer->UnBind();

	m_Shader->UnBind();
}

void CustomLayer::OnImGuiRender()
{
	ImGui::Begin("Example window");
	
	ImGuiIO& io = ImGui::GetIO();
	static float fps = io.Framerate;
	if (m_Timer > 1.0f)
	{
		fps = io.Framerate;
		m_Timer = 0.0f;
	}

	ImGui::Text(fmt::format("FPS: {:.1f}", fps).c_str());

	ImGui::End();
}

void CustomLayer::OnEvent(Event& e)
{
}
