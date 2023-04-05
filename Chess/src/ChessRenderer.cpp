#include "ChessRenderer.hpp"

Board ChessRenderer::s_Board;
pul::Entity ChessRenderer::s_WhiteSquare;
pul::Entity ChessRenderer::s_BlackSquare;

void ChessRenderer::init(SDL_Renderer* renderer)
{
	s_WhiteSquare.setTexture(renderer, "assets/WhiteSquare.png");
	s_WhiteSquare.setRect({ 0.0, 0.0, 100.0, 100.0 });
	s_BlackSquare.setTexture(renderer, "assets/BlackSquare.png");
	s_BlackSquare.setRect({ 100.0, 0.0, 100.0, 100.0 });
}

eqx::Point<double> windowToBoardPoint(eqx::Point<int> p)
{
	return { 25.0 + p.x * 100.0, 25.0 + p.y * 100.0 };
}

void ChessRenderer::render()
{
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if (x % 2 == y % 2)
			{
				s_WhiteSquare.setLocation(windowToBoardPoint({ x, y }));
				s_WhiteSquare.render();
			}
			else
			{
				s_BlackSquare.setLocation(windowToBoardPoint({ x, y }));
				s_BlackSquare.render();
			}
		}
	}
}