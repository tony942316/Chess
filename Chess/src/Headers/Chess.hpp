#pragma once

#include <Pulsar.hpp>

#include "ChessRenderer.hpp"

class Chess
{
public:
	Chess() = delete;
	Chess(const Chess& other) = delete;
	Chess(Chess&& other) = delete;
	Chess& operator= (const Chess& other) = delete;
	Chess& operator= (Chess&& other) = delete;
	~Chess() = delete;

	static void play();

private:
	static void handleEvent(const SDL_Event& e);
	static void update();
	static void render();

	static pul::Window s_Window;
};