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

	static void init(SDL_Renderer* renderer);
	static void render();

private:
	static Board s_Board;
	static pul::Entity s_WhiteSquare;
	static pul::Entity s_BlackSquare;
};