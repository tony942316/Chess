#pragma once

[[nodiscard]] constexpr bool inBounds(const eqx::Point<int>& coord) noexcept
{
	return eqx::intersect(eqx::Rectangle<int>(0, 0, 7, 7), coord);
}

[[nodiscard]] constexpr int coordToIndex(const eqx::Point<int>& coord) noexcept
{
	return coord.x + coord.y * 8;
}

[[nodiscard]] constexpr eqx::Point<int> indexToCoord(int index) noexcept
{
	return eqx::Point<int>(index % 8, index / 8);
}

constexpr Board::Board() noexcept
	:
	m_WhiteRTC({ true, true }),
	m_BlackRTC({ true, true }),
	m_InPassingPiece(eqx::Point<int>(-1, -1)),
	m_Turn(Piece::Color::White)
{
	m_Board[0] = Pieces::Black::Rook;
	m_Board[1] = Pieces::Black::Knight;
	m_Board[2] = Pieces::Black::Bishop;
	m_Board[3] = Pieces::Black::Queen;
	m_Board[4] = Pieces::Black::King;
	m_Board[5] = Pieces::Black::Bishop;
	m_Board[6] = Pieces::Black::Knight;
	m_Board[7] = Pieces::Black::Rook;

	for (std::size_t i = 8ULL; i < 16ULL; i++)
	{
		m_Board[i] = Pieces::Black::Pawn;
	}

	for (std::size_t i = 48ULL; i < 56ULL; i++)
	{
		m_Board[i] = Pieces::White::Pawn;
	}

	m_Board[56] = Pieces::White::Rook;
	m_Board[57] = Pieces::White::Knight;
	m_Board[58] = Pieces::White::Bishop;
	m_Board[59] = Pieces::White::Queen;
	m_Board[60] = Pieces::White::King;
	m_Board[61] = Pieces::White::Bishop;
	m_Board[62] = Pieces::White::Knight;
	m_Board[63] = Pieces::White::Rook;
}

[[nodiscard]] constexpr const Piece& 
	Board::getPiece(const eqx::Point<int>& coord) const noexcept
{
	return m_Board[coordToIndex(coord)];
}

[[nodiscard]] constexpr std::optional<eqx::Point<int>>
	Board::getPiece(const Piece& piece) const noexcept
{
	for (int i = 0; i < m_Board.size(); i++)
	{
		if (m_Board[i] == piece)
		{
			return indexToCoord(i);
		}
	}

	return std::nullopt;
}

[[nodiscard]] constexpr const Piece& 
	Board::walkDir(const eqx::Point<int>& coord, 
		const eqx::Point<int>& dir) const noexcept
{
	auto piece = Piece();
	for (auto loc = coord + dir; inBounds(loc); loc += dir)
	{
		piece = getPiece(loc);
		if (piece.getType() != Piece::Type::None)
		{
			break;
		}
	}
	return piece;
}

[[nodiscard]] constexpr bool
	Board::coordEmpty(const eqx::Point<int>& coord) const noexcept
{
	return getPiece(coord).getType() == Piece::Type::None;
}

constexpr void Board::movePiece(const eqx::Point<int>& pieceCoord,
	const eqx::Point<int>& destCoord) noexcept
{
	m_Board[coordToIndex(destCoord)] = m_Board[coordToIndex(pieceCoord)];
	m_Board[coordToIndex(pieceCoord)] = Piece();
}

constexpr void Board::removePiece(const eqx::Point<int>& pieceCoord) noexcept
{
	m_Board[coordToIndex(pieceCoord)] = Piece();
}

constexpr void Board::setInPassingPiece(const eqx::Point<int>& coord) noexcept
{
	m_InPassingPiece = coord;
}

constexpr void Board::setTurn(Piece::Color color) noexcept
{
	m_Turn = color;
}

[[nodiscard]] constexpr Board::RTC& Board::editRTC(Piece::Color color) noexcept
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

[[nodiscard]] constexpr const std::array<Piece, 64ULL>&
	Board::getBoard() const noexcept
{
	return m_Board;
}

[[nodiscard]] constexpr const Board::RTC& 
	Board::getRTC(Piece::Color color) const noexcept
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

[[nodiscard]] constexpr const eqx::Point<int>&
	Board::getInPassingPiece() const noexcept
{
	return m_InPassingPiece;
}

[[nodiscard]] constexpr Piece::Color Board::getTurn() const noexcept
{
	return m_Turn;
}
