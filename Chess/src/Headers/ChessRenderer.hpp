#pragma once

#include <Pulsar.hpp>

#include "Board.hpp"

class ChessRenderer
{
public:
	ChessRenderer() = delete;
	ChessRenderer(const ChessRenderer& other) = delete;
	ChessRenderer(ChessRenderer&& other) = delete;
	ChessRenderer& operator= (const ChessRenderer& other) = delete;
	ChessRenderer& operator= (ChessRenderer&& other) = delete;
	~ChessRenderer() = delete;

	static void init(pul::Window& window);

	static void handleEvent(const SDL_Event& e);
	static void render();

	static void setBoard(const Board& board);

private:

};