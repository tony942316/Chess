#include "Game.h"

#include <EquinoxSTD.h>

void Game::run()
{
	Game::getInstance().m_Window.setRenders(renders);
	Game::getInstance().m_Window.setCalculations(calculations);
	Game::getInstance().m_Window.setEvents(handleEvents);
	Game::getInstance().m_Window.display();
}

Game::Game()
	:
	m_Window("Game Window", 1600, 900),
	m_Mouse(m_Window, "assets/Flex.png", eqx::Rectangle<double>(0.0, 0.0, 25.0, 25.0), 0.0)
{
}

void Game::renders()
{
	Game::getInstance().m_Mouse.render();
}

void Game::calculations()
{
}

void Game::handleEvents(const SDL_Event& e)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		Game::getInstance().m_Mouse.setLocation(pulsar::Mouse::Location);
	}
}

Game& Game::getInstance()
{
	static Game instance;
	return instance;
}