#pragma once

#include <memory>
#include <filesystem>

namespace Blossom
{

	class RenderController;
	struct UniformElement;

	// TODO(Jorben): Make usable with ImGui?
	class Image
	{
	public:
		Image() = default;
		virtual ~Image() = default;

		virtual void SetData(void* data, size_t size) = 0;

		// Note(Jorben): This function only needs to be called once, when initializing.
		virtual void UploadToController() = 0;

		static std::shared_ptr<Image> Create(std::shared_ptr<RenderController>& controller, UniformElement& element, uint32_t width, uint32_t height);
		static std::shared_ptr<Image> Create(std::shared_ptr<RenderController>& controller, UniformElement& element, const std::filesystem::path& path);
	};

}