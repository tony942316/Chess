#pragma once

#include <string_view>
#include <functional>

#include <EquinoxSTD.hpp>
#define SDL_MAIN_HANDLED
#include <SDL.h>

namespace pul
{
	class Window
	{
	public:
		Window(std::string_view name, int width, int height);
		~Window();

		void show();

		void setEventFunction(
			const std::function<void(const SDL_Event&)>& func);
		void setUpdateFunction(const std::function<void(void)>& func);
		void setRenderFunction(const std::function<void(void)>& func);

		double getDeltaTime() const;
		SDL_Renderer* getRenderer();
		std::string getFPSInfo();

	private:
		void printSDLError() const;
		void printError(std::string_view msg = "") const;

		std::string m_Name;
		int m_Width, m_Height;
		unsigned long long m_FrameCount;
		double m_LastFrameTime;

		std::function<void(const SDL_Event&)> m_EventFunction;
		std::function<void(void)> m_UpdateFunction, m_RenderFunction;

		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;

		eqx::StopWatch m_FrameTimer;
	};
}
