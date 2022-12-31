#pragma once

#include <Pulsar.h>

class Game
{
public:
	static void run();

	Game(const Game& g) = delete;
	void operator= (const Game& g) = delete;

private:
	Game();

	static void renders();
	static void calculations();
	static void handleEvents(const SDL_Event& e);

	static Game& getInstance();

	pulsar::Window m_Window;
	pulsar::Entity m_Mouse;
};