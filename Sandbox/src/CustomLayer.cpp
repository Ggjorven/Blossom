#include "CustomLayer.hpp"

#include <Blossom/Core/Logging.hpp>
#include <Blossom/Renderer/Renderer.hpp>

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>

struct Camera
{
public:
	glm::mat4 Model = {};
	glm::mat4 View = {};
	glm::mat4 Projection = {};
};

void CustomLayer::OnAttach()
{
	Renderer::SetClearColour({ 0.0f, 0.0f, 0.0f, 0.0f });
	
	m_Controller = RenderController::Create();

	m_Mesh = Mesh("assets/objects/viking_room.obj");

	m_Controller->SetBufferLayout(m_Mesh.GetVertexBuffer()->GetLayout());

	// Initialize uniform buffer
	UniformElement texElement = UniformElement(UniformDataType::Image, 0, "u_Texture", UniformElement_Stage_Fragment);
	UniformElement camElement = UniformElement(UniformDataType::UBO, 1, "u_Camera", UniformElement_Stage_Vertex);
	
	UniformLayout uniformlayout = { texElement, camElement };
	m_Controller->SetUniformLayout(uniformlayout);

	m_CameraBuffer = UniformBufferObject::Create(m_Controller, camElement, sizeof(Camera));
	//m_CameraBuffer->SetData((void*)&col, sizeof(Camera));

	m_Image = Image::Create(m_Controller, texElement, "assets/objects/viking_room.png");

	std::shared_ptr<Shader> shader = Shader::Create(Shader::ReadSPIRVFile("assets/shaders/vert.spv"), Shader::ReadSPIRVFile("assets/shaders/frag.spv"));
	m_Controller->SetShader(shader);

	m_Controller->Initialize();

	m_Image->UploadToController();
	m_CameraBuffer->UploadToController();
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

	Camera camera = {};
	camera.Model = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	camera.View = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	camera.Projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f/*TODO PROPERLY IMPLEMENT*/, 0.1f, 10.0f);

	if (Renderer::GetAPI() == RenderingAPI::Vulkan)
		camera.Projection[1][1] *= -1;
	
	m_CameraBuffer->SetData((void*)&camera, sizeof(Camera));
}

void CustomLayer::OnRender()
{
	Renderer::Clear();

	Renderer::AddToQueue([this]() {
		m_Controller->Use();

		m_Mesh.GetVertexBuffer()->Bind();
		m_Mesh.GetIndexBuffer()->Bind();

		Renderer::DrawIndexed(m_Mesh.GetIndexBuffer());

		m_Mesh.GetVertexBuffer()->UnBind();
		m_Mesh.GetIndexBuffer()->UnBind();
	});
}

void CustomLayer::OnImGuiRender()
{
	ImGui::Begin("Example window");
	
	ImGuiIO& io = ImGui::GetIO();
	static float fps = io.Framerate;

	// TODO(Jorben): Fix?
	//if ((int)m_Timer % 2 == 0)
		fps = io.Framerate;

	ImGui::Text(fmt::format("FPS: {:.0f}", fps).c_str());

	ImGui::End();
}

void CustomLayer::OnEvent(Event& e)
{
}
