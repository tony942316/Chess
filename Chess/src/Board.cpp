#include "Board.hpp"

Board::Board()
	:
	m_WhiteRTC({ true, true }),
	m_BlackRTC({ true, true }),
	m_InPassingPiece({ -1, -1 }),
	m_Turn(Piece::Color::White)
{
	m_Board[0] = Piece(Piece::Type::Rook, Piece::Color::Black);
	m_Board[1] = Piece(Piece::Type::Knight, Piece::Color::Black);
	m_Board[2] = Piece(Piece::Type::Bishop, Piece::Color::Black);
	m_Board[3] = Piece(Piece::Type::Queen, Piece::Color::Black);
	m_Board[4] = Piece(Piece::Type::King, Piece::Color::Black);
	m_Board[5] = Piece(Piece::Type::Bishop, Piece::Color::Black);
	m_Board[6] = Piece(Piece::Type::Knight, Piece::Color::Black);
	m_Board[7] = Piece(Piece::Type::Rook, Piece::Color::Black);

	for (std::size_t i = 8ULL; i < 16ULL; i++)
	{
		m_Board[i] = Piece(Piece::Type::Pawn, Piece::Color::Black);
	}

	for (std::size_t i = 48ULL; i < 56ULL; i++)
	{
		m_Board[i] = Piece(Piece::Type::Pawn, Piece::Color::White);
	}

	m_Board[56] = Piece(Piece::Type::Rook, Piece::Color::White);
	m_Board[57] = Piece(Piece::Type::Knight, Piece::Color::White);
	m_Board[58] = Piece(Piece::Type::Bishop, Piece::Color::White);
	m_Board[59] = Piece(Piece::Type::Queen, Piece::Color::White);
	m_Board[60] = Piece(Piece::Type::King, Piece::Color::White);
	m_Board[61] = Piece(Piece::Type::Bishop, Piece::Color::White);
	m_Board[62] = Piece(Piece::Type::Knight, Piece::Color::White);
	m_Board[63] = Piece(Piece::Type::Rook, Piece::Color::White);
}

const Piece& Board::getPiece(const eqx::Point<int>& coord) const
{
	return m_Board.at(coordToIndex(coord));
}

std::vector<eqx::Point<int>> Board::getAllPieces() const
{
	auto result = std::vector<eqx::Point<int>>();
	result.reserve(32ULL);
	for (int i = 0; i < m_Board.size(); i++)
	{
		if (m_Board.at(i).getType() != Piece::Type::None)
		{
			result.emplace_back(indexToCoord(i));
		}
	}

	return result;
}

void Board::movePiece(const eqx::Point<int>& pieceCoord, 
	const eqx::Point<int>& destCoord)
{
	m_Board[coordToIndex(destCoord)] = m_Board[coordToIndex(pieceCoord)];
	m_Board[coordToIndex(pieceCoord)] = Piece();
}

const Board::RTC& Board::getRTC(Piece::Color color) const noexcept
{
	if (color == Piece::Color::White)
	{
		return m_WhiteRTC;
	}
	else
	{
		return m_BlackRTC;
	}
}

Board::RTC& Board::editRTC(Piece::Color color) noexcept
{
	if (color == Piece::Color::White)
	{
		return m_WhiteRTC;
	}
	else
	{
		return m_BlackRTC;
	}
}

const std::array<Piece, 64ULL>& Board::getBoard() const noexcept
{
	return m_Board;
}

const eqx::Point<int>& Board::getInPassingPiece() const noexcept
{
	return m_InPassingPiece;
}

void Board::setInPassingPiece(const eqx::Point<int>& coord) noexcept
{
	m_InPassingPiece = coord;
}

Piece::Color Board::getTurn() const noexcept
{
	return m_Turn;
}

void Board::setTurn(Piece::Color color) noexcept
{
	m_Turn = color;
}

constexpr int Board::coordToIndex(const eqx::Point<int>& coord) const noexcept
{
	return coord.x + coord.y * 8;
}

constexpr eqx::Point<int> Board::indexToCoord(int index) const noexcept
{
	return { index % 8 , index / 8 };
}
