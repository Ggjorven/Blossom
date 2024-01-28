#include "blpch.h"
#include "OpenGLRenderer.hpp"

#include "Blossom/Core/Application.hpp"

#include "Blossom/Core/Logging.hpp"

#include <GL/glew.h>

namespace Blossom
{

	Renderer* Renderer::s_Instance = nullptr;

	void Renderer::Init()
	{
		s_Instance = new Renderer();
	}

	void Renderer::Destroy()
	{
		delete s_Instance;
		s_Instance = nullptr;
	}

	void Renderer::AddToQueue(RenderFunction func)
	{
		s_Instance->m_RenderQueue.push_back(func);
	}

	void Renderer::AddToUIQueue(UIFunction func)
	{
		s_Instance->m_UIQueue.push_back(func);
	}

	void Renderer::Display()
	{
		s_Instance->m_RenderQueue.clear();
		s_Instance->m_UIQueue.clear();
	}

	void Renderer::OnResize(uint32_t width, uint32_t height)
	{
		glViewport(0, 0, width, height);
	}

}