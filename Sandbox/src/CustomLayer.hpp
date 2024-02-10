#pragma once

#include <Blossom/Core/Layer.hpp>
#include <Blossom/Renderer/RenderController.hpp>
#include <Blossom/Renderer/VertexBuffer.hpp>
#include <Blossom/Renderer/IndexBuffer.hpp>
#include <Blossom/Renderer/UniformBuffer.hpp>
#include <Blossom/Renderer/Image.hpp>
#include <Blossom/Renderer/Shader.hpp>
#include <Blossom/Utils/Mesh.hpp>

using namespace Blossom;

class CustomLayer : public Layer
{
public:
	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(float deltaTime) override;
	void OnRender();
	void OnImGuiRender() override;

	void OnEvent(Event& e);

private:
	Mesh m_Mesh = {};

	std::shared_ptr<UniformBufferObject> m_CameraBuffer = nullptr;
	std::shared_ptr<Image> m_Image = nullptr;

	std::shared_ptr<RenderController> m_Controller = nullptr;

	float m_Timer = 0.0f; // For FPS updates
};