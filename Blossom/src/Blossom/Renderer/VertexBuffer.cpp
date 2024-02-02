#include "blpch.h"
#include "VertexBuffer.hpp"

#include "Blossom/Core/Logging.hpp"

#include "Blossom/Renderer/Renderer.hpp"

#include "Blossom/APIs/OpenGL/OpenGLVertexBuffer.hpp"
#include "Blossom/APIs/Vulkan/VulkanVertexBuffer.hpp"

namespace Blossom
{

	uint32_t BufferDataTypeSize(BufferDataType type)
	{
		switch (type)
		{
		case BufferDataType::Float:    return 4;
		case BufferDataType::Float2:   return 4 * 2;
		case BufferDataType::Float3:   return 4 * 3;
		case BufferDataType::Float4:   return 4 * 4;
		case BufferDataType::Mat3:     return 4 * 3 * 3;
		case BufferDataType::Mat4:     return 4 * 4 * 4;
		case BufferDataType::Int:      return 4;
		case BufferDataType::Int2:     return 4 * 2;
		case BufferDataType::Int3:     return 4 * 3;
		case BufferDataType::Int4:     return 4 * 4;
		case BufferDataType::Bool:     return 1;
		}

		BL_LOG_ERROR("Unknown ShaderDataType!");
		return 0;
	}

	BufferElement::BufferElement(BufferDataType type, uint32_t location, const std::string& name, bool normalized)
		: Name(name), Location(location), Type(type), Size(BufferDataTypeSize(type)), Offset(0), Normalized(normalized)
	{
	}

	uint32_t BufferElement::GetComponentCount() const
	{
		switch (Type)
		{
		case BufferDataType::Float:   return 1;
		case BufferDataType::Float2:  return 2;
		case BufferDataType::Float3:  return 3;
		case BufferDataType::Float4:  return 4;
		case BufferDataType::Mat3:    return 3 * 3;
		case BufferDataType::Mat4:    return 4 * 4;
		case BufferDataType::Int:     return 1;
		case BufferDataType::Int2:    return 2;
		case BufferDataType::Int3:    return 3;
		case BufferDataType::Int4:    return 4;
		case BufferDataType::Bool:    return 1;
		}

		BL_LOG_ERROR("Unknown ShaderDataType!");
		return 0;
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
		: m_Elements(elements)
	{
		CalculateOffsetsAndStride();
	}

	void BufferLayout::CalculateOffsetsAndStride()
	{
		size_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(void* data, size_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderingAPI::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(data, size);
		case RenderingAPI::Vulkan:
			return std::make_shared<VulkanVertexBuffer>(data, size);

		default:
			BL_LOG_ERROR("Unknown Renderer::API selected.");
			break;
		}

		return nullptr;
	}

}