#include "ChessRenderer.hpp"

#include <array>

static std::array<pul::Entity*, 64ULL> arr;
static eqx::Point<int> s_HeldPiece = { -1, -1 };

static double s_Scale = 125.0;
static eqx::Rectangle<double> s_Location;

static pul::Entity s_WhiteSquare;
static pul::Entity s_BlackSquare;

static pul::Entity s_BlackRook;
static pul::Entity s_BlackKnight;
static pul::Entity s_BlackBishop;
static pul::Entity s_BlackQueen;
static pul::Entity s_BlackKing;
static pul::Entity s_BlackPawn;
static pul::Entity s_WhiteRook;
static pul::Entity s_WhiteKnight;
static pul::Entity s_WhiteBishop;
static pul::Entity s_WhiteQueen;
static pul::Entity s_WhiteKing;
static pul::Entity s_WhitePawn;

static pul::Entity s_Frame;

static Board s_Board;

void ChessRenderer::init(pul::Window& window)
{
	s_Location.x = (window.getWidth() - s_Scale * 8.0) / 2.0;
	s_Location.y = (window.getHeight() - s_Scale * 8.0) / 2.0;
	s_Location.w = s_Scale * 8.0;
	s_Location.h = s_Scale * 8.0;

	s_WhiteSquare.setTexture(window.getRenderer(), "assets/WhiteSquare.png");
	s_WhiteSquare.setRect({ 0.0, 0.0, s_Scale, s_Scale });
	s_BlackSquare.setTexture(window.getRenderer(), "assets/BlackSquare.png");
	s_BlackSquare.setRect({ 0.0, 0.0, s_Scale, s_Scale });

	s_BlackRook.setTexture(window.getRenderer(), "assets/BlackRook.png");
	s_BlackRook.setRect({ 0.0, 0.0, s_Scale, s_Scale });
	s_BlackKnight.setTexture(window.getRenderer(), "assets/BlackKnight.png");
	s_BlackKnight.setRect({ 0.0, 0.0, s_Scale, s_Scale });
	s_BlackBishop.setTexture(window.getRenderer(), "assets/BlackBishop.png");
	s_BlackBishop.setRect({ 0.0, 0.0, s_Scale, s_Scale });
	s_BlackQueen.setTexture(window.getRenderer(), "assets/BlackQueen.png");
	s_BlackQueen.setRect({ 0.0, 0.0, s_Scale, s_Scale });
	s_BlackKing.setTexture(window.getRenderer(), "assets/BlackKing.png");
	s_BlackKing.setRect({ 0.0, 0.0, s_Scale, s_Scale });
	s_BlackPawn.setTexture(window.getRenderer(), "assets/BlackPawn.png");
	s_BlackPawn.setRect({ 0.0, 0.0, s_Scale, s_Scale });

	s_WhiteRook.setTexture(window.getRenderer(), "assets/WhiteRook.png");
	s_WhiteRook.setRect({ 0.0, 0.0, s_Scale, s_Scale });
	s_WhiteKnight.setTexture(window.getRenderer(), "assets/WhiteKnight.png");
	s_WhiteKnight.setRect({ 0.0, 0.0, s_Scale, s_Scale });
	s_WhiteBishop.setTexture(window.getRenderer(), "assets/WhiteBishop.png");
	s_WhiteBishop.setRect({ 0.0, 0.0, s_Scale, s_Scale });
	s_WhiteQueen.setTexture(window.getRenderer(), "assets/WhiteQueen.png");
	s_WhiteQueen.setRect({ 0.0, 0.0, s_Scale, s_Scale });
	s_WhiteKing.setTexture(window.getRenderer(), "assets/WhiteKing.png");
	s_WhiteKing.setRect({ 0.0, 0.0, s_Scale, s_Scale });
	s_WhitePawn.setTexture(window.getRenderer(), "assets/WhitePawn.png");
	s_WhitePawn.setRect({ 0.0, 0.0, s_Scale, s_Scale });

	s_Frame.setTexture(window.getRenderer(), "assets/Frame.png");
	s_Frame.setRect({ 0.0, 0.0, s_Scale, s_Scale });

	setBoard(Board());
}

eqx::Point<double> boardToWindowPoint(const eqx::Point<int>& p)
{
	return { 
		s_Location.x + p.x * s_Scale, 
		s_Location.y + p.y * s_Scale };
}

eqx::Point<int> windowToBoardPoint(const eqx::Point<double>& p)
{
	eqx::Point<int> result = {
		static_cast<int>((p.x - s_Location.x) / s_Scale),
		static_cast<int>((p.y - s_Location.y) / s_Scale) };
	if (result.x == 8)
	{
		result.x--;
	}
	if (result.y == 8)
	{
		result.y--;
	}
	return result;
}

pul::Entity* getEntity(char c)
{
	switch (c)
	{
	case 'r':
		return &s_BlackRook;
		break;
	case 'n':
		return &s_BlackKnight;
		break;
	case 'b':
		return &s_BlackBishop;
		break;
	case 'q':
		return &s_BlackQueen;
		break;
	case 'k':
		return &s_BlackKing;
		break;
	case 'p':
		return &s_BlackPawn;
		break;
	case 'R':
		return &s_WhiteRook;
		break;
	case 'N':
		return &s_WhiteKnight;
		break;
	case 'B':
		return &s_WhiteBishop;
		break;
	case 'Q':
		return &s_WhiteQueen;
		break;
	case 'K':
		return &s_WhiteKing;
		break;
	case 'P':
		return &s_WhitePawn;
		break;
	case '-':
		return nullptr;
		break;
	default:
		break;
	}

	return nullptr;
}

void ChessRenderer::handleEvent(const SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			const auto& clickLocation = pul::Mouse::getLeftClickDownLocation();
			if (eqx::intersect(s_Location, clickLocation))
			{
				s_HeldPiece = windowToBoardPoint(clickLocation);
			}
		}
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			s_HeldPiece = { -1, -1 };
		}
	}
}

void ChessRenderer::render()
{
	auto iter = 0ULL;
	auto windowPoint = eqx::Point<double>();
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			windowPoint = boardToWindowPoint({ x, y });
			if (x % 2 == y % 2)
			{
				s_WhiteSquare.setLocation(windowPoint);
				s_WhiteSquare.render();
			}
			else
			{
				s_BlackSquare.setLocation(windowPoint);
				s_BlackSquare.render();
			}

			if (arr[iter] != nullptr &&
				eqx::Point<int>({ x, y }) != s_HeldPiece)
			{
				arr[iter]->setLocation(windowPoint);
				arr[iter]->render();
			}

			iter++;
		}
	}

	const auto& mouseLocation = pul::Mouse::getCurrentLocation();
	if (s_HeldPiece != eqx::Point<int>({ -1, -1 }))
	{
		s_Frame.setLocation(boardToWindowPoint(s_HeldPiece));
		s_Frame.render();
	}
	else
	{
		auto boardPoint = eqx::Point<int>();
		if (eqx::intersect(s_Location, mouseLocation))
		{
			windowPoint = boardToWindowPoint(
				windowToBoardPoint(mouseLocation));
			boardPoint = windowToBoardPoint(windowPoint);
			if (arr.at(boardPoint.x + boardPoint.y * 8) != nullptr)
			{
				s_Frame.setLocation(windowPoint);
				s_Frame.render();
			}
		}
	}
	

	if (s_HeldPiece != eqx::Point<int>({ -1, -1 }))
	{
		auto* piece = arr.at(s_HeldPiece.x + s_HeldPiece.y * 8);
		auto pieceLoc = boardToWindowPoint(s_HeldPiece);
		auto dx = pul::Mouse::getLeftClickDownLocation().x - pieceLoc.x;
		auto dy = pul::Mouse::getLeftClickDownLocation().y - pieceLoc.y;
		auto drawLoc = eqx::Point<double>({
			mouseLocation.x - dx,
			mouseLocation.y - dy });
		piece->setLocation(drawLoc);
		piece->render();
	}
}

void ChessRenderer::setBoard(const Board& board)
{
	s_Board = board;

	auto* piece = static_cast<pul::Entity*>(nullptr);
	for (std::size_t i = 0ULL; i < arr.size(); i++)
	{
		piece = getEntity(s_Board.getBoard().at(i));
		arr[i] = piece;
	}
}