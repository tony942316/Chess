#pragma once

#include <string>
#include <functional>
#include <unordered_map>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <EquinoxSTD.h>

namespace pulsar
{
	class Window
	{
	public:
		enum class Package
		{
			Standard,
			NoVsync
		};

		Window(const std::string& name, int width, int height, Window::Package package = Window::Package::Standard);
		~Window();


		void setCalculations(std::function<void()> calcFunction);
		void setRenders(std::function<void()> renderFunction);
		void setEvents(std::function<void(const SDL_Event&)> eventFunction);
		void hideMouse();
		void showMouse();
		void display();
		void exit();

		SDL_Window* getWindow() const;
		SDL_Renderer* getRenderer() const;
		int getWidth() const;
		int getHeight() const;
		double getAvgFrameTime() const;
		double getAvgFps() const;
		double getCurrentFps() const;
		long long getLastFrameTime() const;
		double getDeltaTime() const;

		void printFrameInfo() const;

	private:
		std::unordered_map<Window::Package, std::pair<int, int>> m_Packages;
		Window::Package m_Package;

		int pollEvent();
		SDL_Event getEvent() const;
		bool quit();
		void clear();
		void show();

		bool init();
		bool initSDL();
		bool createWindow();
		bool createRenderer();
		void close();

		SDL_Window* m_Window;
		SDL_Renderer* m_Renderer;
		SDL_Event m_Event;
		SDL_GameController* m_Gamepad;
		eqx::StopWatch m_FrameTimer;
		int m_ScreenWidth, m_ScreenHeight;
		long long int m_FrameCount, m_LastFrameTime;
		double m_AvgFrameTime, m_TotalFrameTime;
		bool m_Exit;
		std::function<void()> m_CalcFunc, m_RenderFunc;
		std::function<void(const SDL_Event&)> m_EventFunc;
		std::string m_WindowName;
	};
}