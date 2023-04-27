#include "ChessRenderer.hpp"

#include <string_view>

#include <array>
#include <unordered_map>

#include "Analyzer.hpp"

static constexpr double c_Scale = 125.0;
static eqx::Rectangle<double> s_Location;
static SDL_Renderer* s_Renderer;

static pul::Texture s_WhiteSquareTexture;
static pul::Texture s_BlackSquareTexture;
static pul::Texture s_FrameTexture;
static std::unordered_map<Piece, pul::Texture> s_PieceTextures;

static pul::Entity s_Frame;
static std::unordered_map<int, pul::Entity> s_Pieces;
static std::array<pul::Entity, 64ULL> s_Squares;
static pul::Entity* s_HeldPiece = nullptr;

static std::array<std::unordered_map<Move, Board>, 64ULL> s_Moves;
static Board s_Board;
static std::vector<pul::Entity> s_MoveEntities;

eqx::Point<int> windowToBoardSpace(const eqx::Point<double>& point)
{
	return eqx::Point<int>(
		static_cast<int>(std::floor((point.x - s_Location.x) / c_Scale)),
		static_cast<int>(std::floor((point.y - s_Location.y) / c_Scale)));
}

eqx::Point<double> boardToWindowSpace(const eqx::Point<int>& coord)
{
	return eqx::Point<double>(
		s_Location.x + coord.x * c_Scale,
		s_Location.y + coord.y * c_Scale);
}

void ChessRenderer::init(pul::Window& window)
{
	s_Location.x = (window.getWidth() - c_Scale * 8.0) / 2.0;
	s_Location.y = (window.getHeight() - c_Scale * 8.0) / 2.0;
	s_Location.w = c_Scale * 8.0;
	s_Location.h = c_Scale * 8.0;

	s_Renderer = window.getRenderer();

	s_WhiteSquareTexture = 
		pul::Texture(s_Renderer, "assets/WhiteSquare.png");
	s_BlackSquareTexture =
		pul::Texture(s_Renderer, "assets/BlackSquare.png");
	s_FrameTexture =
		pul::Texture(s_Renderer, "assets/Frame.png");

	s_PieceTextures.emplace(Pieces::Black::Rook,
		pul::Texture(s_Renderer, "assets/BlackRook.png"));
	s_PieceTextures.emplace(Pieces::Black::Knight,
		pul::Texture(s_Renderer, "assets/BlackKnight.png"));
	s_PieceTextures.emplace(Pieces::Black::Bishop,
		pul::Texture(s_Renderer, "assets/BlackBishop.png"));
	s_PieceTextures.emplace(Pieces::Black::Queen,
		pul::Texture(s_Renderer, "assets/BlackQueen.png"));
	s_PieceTextures.emplace(Pieces::Black::King,
		pul::Texture(s_Renderer, "assets/BlackKing.png"));
	s_PieceTextures.emplace(Pieces::Black::Pawn,
		pul::Texture(s_Renderer, "assets/BlackPawn.png"));

	s_PieceTextures.emplace(Pieces::White::Rook,
		pul::Texture(s_Renderer, "assets/WhiteRook.png"));
	s_PieceTextures.emplace(Pieces::White::Knight,
		pul::Texture(s_Renderer, "assets/WhiteKnight.png"));
	s_PieceTextures.emplace(Pieces::White::Bishop,
		pul::Texture(s_Renderer, "assets/WhiteBishop.png"));
	s_PieceTextures.emplace(Pieces::White::Queen,
		pul::Texture(s_Renderer, "assets/WhiteQueen.png"));
	s_PieceTextures.emplace(Pieces::White::King,
		pul::Texture(s_Renderer, "assets/WhiteKing.png"));
	s_PieceTextures.emplace(Pieces::White::Pawn,
		pul::Texture(s_Renderer, "assets/WhitePawn.png"));

	s_Frame = pul::Entity(s_FrameTexture, 
		eqx::Rectangle<double>(0.0, 0.0, c_Scale, c_Scale), 900.0);

	auto currentLocation = eqx::Rectangle<double>();
	auto i = 0ULL;
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			currentLocation = eqx::Rectangle<double>(
				x * c_Scale + s_Location.x,
				y * c_Scale + s_Location.y,
				c_Scale,
				c_Scale);

			s_Squares[i].setDrawBox(currentLocation);
			if (x % 2 == y % 2)
			{
				s_Squares[i].setTexture(s_WhiteSquareTexture);
			}
			else
			{
				s_Squares[i].setTexture(s_BlackSquareTexture);
			}
			i++;
		}
	}

	setBoard(Board());
}

void ChessRenderer::setBoard(const Board& board)
{
	s_Pieces.clear();
	s_Board = board;

	auto piece = Piece();
	auto location = eqx::Rectangle<double>();
	auto destination = eqx::Point<double>();
	auto entity = pul::Entity();
	for (int i = 0; i < board.getBoard().size(); i++)
	{
		piece = board.getBoard().at(i);
		location = eqx::Rectangle<double>(
			0.0,
			0.0,
			c_Scale,
			c_Scale);
		destination = eqx::Point<double>(
			s_Location.x + c_Scale * (i % 8),
			s_Location.y + c_Scale * (i / 8));

		if (piece.getType() != Piece::Type::None)
		{
			entity = 
				pul::Entity(s_PieceTextures.at(piece), location, 2'000.0);
			entity.setTarget(destination);
			entity.setRotationSpeed(300.0);
			entity.setRotationPoint(eqx::Point<double>(
				c_Scale / 2.0, c_Scale / 2.0));
			s_Pieces.emplace(i, entity);

			s_Moves[i] = Analyzer::getAllPermutations(s_Board);
		}
	}
}

void ChessRenderer::handleEvent(const SDL_Event& e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		auto coord = windowToBoardSpace(pul::Mouse::getCurrentLocation());
		auto index = coordToIndex(coord);
		if (e.button.button == SDL_BUTTON_LEFT &&
			inBounds(coord) &&
			s_Pieces.contains(index))
		{
			s_HeldPiece = &s_Pieces.at(index);
			std::ranges::for_each(s_Moves.at(index),
				[](const auto& valPair)
				{
					auto location = 
						boardToWindowSpace(valPair.first.getDest());
					auto drawLocation = eqx::Rectangle<double>(
						location.x,
						location.y,
						c_Scale,
						c_Scale);
					s_MoveEntities.emplace_back(
						pul::Entity(s_FrameTexture, drawLocation, 0.0));
					s_MoveEntities.back().setColor({ 0, 255, 0 });
				});
		}
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		if (e.button.button == SDL_BUTTON_LEFT &&
			s_HeldPiece != nullptr)
		{
			auto moveLocation = boardToWindowSpace(windowToBoardSpace(
				pul::Mouse::getLeftClickDownLocation()));
			auto validMove = false;
			for (const auto& val : s_MoveEntities)
			{
				if (eqx::intersect(val.getDrawBox(),
					pul::Mouse::getLeftClickUpLocation()))
				{
					moveLocation = boardToWindowSpace(windowToBoardSpace(
						pul::Mouse::getLeftClickUpLocation()));
					validMove = true;
				}
			}
			s_HeldPiece->setTarget(moveLocation);
			s_HeldPiece->setRotationTarget(0.0);
			s_HeldPiece = nullptr;
			s_MoveEntities.clear();
			if (validMove)
			{
				auto move = Move(
					windowToBoardSpace(pul::Mouse::getLeftClickDownLocation()),
					windowToBoardSpace(pul::Mouse::getLeftClickUpLocation()),
					Move::Type::None);
				auto index = coordToIndex(move.getSource());
				setBoard(s_Moves.at(index).at(move));
			}
			
		}
	}
}

void ChessRenderer::update(double dt)
{
	auto location = boardToWindowSpace(windowToBoardSpace(
		pul::Mouse::getCurrentLocation()));
	auto mouseIndex = 
		coordToIndex(windowToBoardSpace(pul::Mouse::getCurrentLocation()));

	if (s_HeldPiece == nullptr &&
		inBounds(windowToBoardSpace(pul::Mouse::getCurrentLocation())) &&
		s_Pieces.contains(mouseIndex))
	{
		s_Frame.setLocation(location);
	}
	else if (s_HeldPiece == nullptr)
	{
		s_Frame.setLocation(eqx::Point<double>(-c_Scale, -c_Scale));
	}

	if (s_HeldPiece != nullptr)
	{
		auto trackLocation = pul::Mouse::getCurrentLocation() -
			eqx::Point<double>(c_Scale / 2.0, c_Scale / 2.0);
		s_HeldPiece->setTarget(trackLocation);
		if (!s_HeldPiece->targetReached())
		{
			s_HeldPiece->setRotationTarget(
				eqx::getSign(s_HeldPiece->getDirection().x) * 30.0);
		}
		else
		{
			s_HeldPiece->setRotationTarget(0.0);
		}
	}

	std::ranges::for_each(s_Pieces,
		[dt = dt](auto& valPair)
		{
			valPair.second.move(dt);
			valPair.second.rotate(dt);
		});
}

void ChessRenderer::render()
{
	std::ranges::for_each(s_Squares,
		[](const auto& val)
		{
			val.render();
		});

	std::ranges::for_each(s_Pieces,
		[](const auto& valPair)
		{
			valPair.second.render();
		});

	std::ranges::for_each(s_MoveEntities,
		[](const auto& val)
		{
			val.render();
		});

	s_Frame.render();

	if (s_HeldPiece != nullptr)
	{
		s_HeldPiece->render();
	}
}