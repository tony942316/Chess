#include "Chess.hpp"

#include <iostream>

pul::Window Chess::s_Window = { "Chess", 1800, 1200 };

void Chess::play()
{
	ChessRenderer::init(s_Window);

	s_Window.setEventFunction(handleEvent);
	s_Window.setUpdateFunction(update);
	s_Window.setRenderFunction(render);

	s_Window.show();
}

void Chess::handleEvent(const SDL_Event& e)
{
	ChessRenderer::handleEvent(e);
}

void Chess::update()
{
	static auto timer = eqx::StopWatch();
	if (timer.readTime() > 1'000)
	{
		timer.start();
		std::cout << s_Window.getFPSInfo() << std::endl;
	}
}

void Chess::render()
{
	ChessRenderer::render();
}