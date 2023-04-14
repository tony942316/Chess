#pragma once

#include <Pulsar.hpp>

#include "Board.hpp"

namespace ChessRenderer
{
	void init(pul::Window& window);

	void handleEvent(const SDL_Event& e);
	void update(double dt);
	void render();

	void setBoard(const Board& board);
}