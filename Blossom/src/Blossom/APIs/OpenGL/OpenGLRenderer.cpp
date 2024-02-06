#include "blpch.h"
#include "OpenGLRenderer.hpp"

#include <GL/glew.h>

#include "Blossom/Renderer/VertexBuffer.hpp"
#include "Blossom/Renderer/IndexBuffer.hpp"

#include "Blossom/Utils/Profiler.hpp"

namespace Blossom
{

	void OpenGLRenderer::WaitImpl()
	{
		// Note(Jorben): This function is irrevelant for OpenGL
	}

	void OpenGLRenderer::ClearImpl()
	{
		glClear((unsigned int)Renderer::GetAPISpecs().ClearValues);
	}

	void OpenGLRenderer::SetClearColourImpl(const glm::vec4& colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);
		Renderer::GetAPISpecs().ClearColour = colour;
	}

	void OpenGLRenderer::DrawIndexedImpl(std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRenderer::OnResizeImpl(uint32_t width, uint32_t height)
	{
		glViewport(0, 0, width, height);
	}

	void OpenGLRenderer::AddToQueueImpl(RenderFunction function)
	{
		m_RenderFunctions.push(function);
	}

	void OpenGLRenderer::AddToUIQueueImpl(UIFunction function)
	{
		// Note(Jorben): This method is irrelevant for OpenGL compared to Vulkan
	}

	void OpenGLRenderer::DisplayImpl()
	{
		{
			BL_PROFILE_SCOPE("Display");
			while (!m_RenderFunctions.empty())
			{
				auto& func = m_RenderFunctions.front();
				func();
				m_RenderFunctions.pop();
			}
		}
	}

}