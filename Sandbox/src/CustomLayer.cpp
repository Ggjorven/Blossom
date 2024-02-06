#include "CustomLayer.hpp"

#include <Blossom/Core/Logging.hpp>
#include <Blossom/Renderer/Renderer.hpp>

#include <imgui.h>

void CustomLayer::OnAttach()
{
	Renderer::SetClearColour({ 0.0f, 0.0f, 0.0f, 0.0f });

	float squareVertices[6 * 4] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f
	};

	uint32_t squareIndices[6] = {
		0, 1, 2,
		2, 3, 0
	};
	
	m_Controller = RenderController::Create();

	m_VertexBuffer = VertexBuffer::Create((void*)squareVertices, sizeof(squareVertices));
	BufferLayout layout = {
		BufferElement(BufferDataType::Float3, 0, "a_Position", false),
		BufferElement(BufferDataType::Float3, 1, "a_Colour", false)
	};
	m_VertexBuffer->SetLayout(layout);

	m_Controller->SetBufferLayout(layout);

	m_IndexBuffer = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

	// Initialize uniform buffer
	UniformElement colourElement = UniformElement(UniformDataType::UBO, 0, "u_Colour", UniformElement_Stage_Fragment);
	
	UniformLayout uniformlayout = { colourElement };
	m_Controller->SetUniformLayout(uniformlayout);

	m_UniformBuffer = UniformBufferObject::Create(m_Controller, colourElement, sizeof(glm::vec4));

	// Note(Jorben): The data can be set from anywhere and doesn't even need to be setup here beforehand
	glm::vec4 col = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	m_UniformBuffer->SetData((void*)&col, sizeof(glm::vec4));

	std::shared_ptr<Shader> shader = Shader::Create(Shader::ReadSPIRVFile("assets/shaders/vert.spv"), Shader::ReadSPIRVFile("assets/shaders/frag.spv"));
	m_Controller->SetShader(shader);

	m_Controller->Initialize();
	m_UniformBuffer->UploadToController();
}

void CustomLayer::OnDetach()
{
}

void CustomLayer::OnUpdate(float deltaTime)
{
	m_Timer += deltaTime;

	float r = 0.5f * (1.0f + glm::sin(m_Timer * 2.0f * 3.1415f));
	float g = 0.5f * (1.0f + glm::sin(m_Timer * 2.0f * 3.1415f + 2.0f * 3.1415f / 3.0f));
	float b = 0.5f * (1.0f + glm::sin(m_Timer * 2.0f * 3.1415f + 4.0f * 3.1415f / 3.0f));

	glm::vec4 col = glm::vec4(r, g, b, 1.0f);

	m_UniformBuffer->SetData((void*)&col, sizeof(glm::vec4));
}

void CustomLayer::OnRender()
{
	Renderer::Clear();

	Renderer::AddToQueue([this]() {
		m_Controller->Use();

		m_VertexBuffer->Bind();
		m_IndexBuffer->Bind();

		Renderer::DrawIndexed(m_IndexBuffer);

		m_IndexBuffer->UnBind();
		m_VertexBuffer->UnBind();
	});
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

	ImGui::Text(fmt::format("FPS: {:.0f}", fps).c_str());

	ImGui::End();
}

void CustomLayer::OnEvent(Event& e)
{
}
