#pragma once

#include <functional>
#include <vector>

namespace Blossom
{

	typedef std::function<void()> RenderFunction;
	typedef std::function<void()> UIFunction;

	class Renderer
	{
	public:
		static Renderer* Get() { return s_Instance; }

		static void Init();
		static void Destroy();

		static void AddToQueue(RenderFunction func);
		static void AddToUIQueue(UIFunction func);
		static void Display();

		static void OnResize(uint32_t width, uint32_t height);

	private:
		static Renderer* s_Instance;

	private:
		std::vector<RenderFunction> m_RenderQueue = { };
		std::vector<UIFunction> m_UIQueue = { };

	};

}