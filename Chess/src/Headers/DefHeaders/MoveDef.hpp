#pragma once

[[nodiscard]] constexpr bool inBounds(const Move& move) noexcept
{
	return inBounds(move.getSource()) && inBounds(move.getDest());
}

constexpr Move::Move() noexcept
	:
	m_Source(eqx::Point<int>()),
	m_Dest(eqx::Point<int>()),
	m_Type(Type::None)
{
}

constexpr Move::Move(const eqx::Point<int>& source,
	const eqx::Point<int>& dest, Type type) noexcept
	:
	m_Source(source),
	m_Dest(dest),
	m_Type(type)
{
}

[[nodiscard]] constexpr bool 
	Move::operator== (const Move& other) const noexcept
{
	return m_Source == other.m_Source &&
		m_Dest == other.m_Dest &&
		m_Type == other.m_Type;
}

[[nodiscard]] constexpr bool Move::isValid(const Board& board) const
{
	if (!inBounds(*this) ||
		board.getPiece(m_Source).getType() == Piece::Type::None ||
		board.getPiece(m_Source).getColor() != board.getTurn())
	{
		return false;
	}

	auto checkForCheck = Board(board);
	checkForCheck.movePiece(m_Source, m_Dest);
	if (inCheck(checkForCheck, board.getPiece(m_Source).getColor()))
	{
		return false;
	}

	switch (m_Type)
	{
	case Type::Slide:
		return validSlide(board);
		break;
	case Type::Jump:
		return validJump(board);
		break;
	case Type::PawnDouble:
		return validPawnDouble(board);
		break;
	case Type::EnPassant:
		return validEnPassant(board);
		break;
	case Type::LongCastle:
		return validCastle(board);
		break;
	case Type::ShortCastle:
		return validCastle(board);
		break;
	case Type::None:
		return false;
		break;
	default:
		return false;
		break;
	}
}

[[nodiscard]] constexpr Board Move::apply(const Board& board) const noexcept
{
	auto result = Board(board);
	result.movePiece(m_Source, m_Dest);
	result.setInPassingPiece(eqx::Point<int>(-1, -1));
	result.setTurn(!board.getTurn());

	auto castleRook = eqx::Point<int>();
	if (board.getPiece(m_Source).getColor() == Piece::Color::White)
	{
		castleRook.y = 7;
	}

	switch (m_Type)
	{
	case Type::Slide:
		break;
	case Type::Jump:
		break;
	case Type::PawnDouble:
		result.setInPassingPiece(m_Dest);
		break;
	case Type::EnPassant:
		result.removePiece(board.getInPassingPiece());
		break;
	case Type::LongCastle:
		castleRook.x = 0;
		result.movePiece(castleRook, eqx::Point<int>(3, castleRook.y));
		break;
	case Type::ShortCastle:
		castleRook.x = 7;
		result.movePiece(castleRook, eqx::Point<int>(5, castleRook.y));
		break;
	case Type::None:
		break;
	default:
		break;
	}

	return result;
}

constexpr void Move::setSource(const eqx::Point<int>& source) noexcept
{
	m_Source = source;
}

constexpr void Move::setDest(const eqx::Point<int>& dest) noexcept
{
	m_Dest = dest;
}

constexpr void Move::setType(Type type) noexcept
{
	m_Type = type;
}

[[nodiscard]] constexpr const eqx::Point<int>& Move::getSource() const noexcept
{
	return m_Source;
}

[[nodiscard]] constexpr const eqx::Point<int>& Move::getDest() const noexcept
{
	return m_Dest;
}

[[nodiscard]] constexpr Move::Type Move::getType() const noexcept
{
	return m_Type;
}

[[nodiscard]] constexpr bool Move::pathClear(const Board& board) const noexcept
{
	auto dir = m_Dest - m_Source;
	dir.x = eqx::getSign(dir.x);
	dir.y = eqx::getSign(dir.y);

	for (auto loc = m_Source + dir; loc != m_Dest; loc += dir)
	{
		if (board.getPiece(loc).getColor() != Piece::Color::None)
		{
			return false;
		}
	}

	return true;
}

[[nodiscard]] constexpr bool
	Move::squareOpposed(const Board& board) const noexcept
{
	auto pieceColor = board.getPiece(m_Source).getColor();
	auto opposingColor = board.getPiece(m_Dest).getColor();

	if (pieceColor != opposingColor &&
		!board.coordEmpty(m_Dest))
	{
		return true;
	}
	else
	{
		return false;
	}
}

[[nodiscard]] constexpr bool
	Move::squareTakable(const Board& board) const noexcept
{
	return board.coordEmpty(m_Dest) || squareOpposed(board);
}

[[nodiscard]] constexpr bool
	Move::inCheck(const Board& board, Piece::Color color)
{
	auto result = false;
	const auto& kingCoord =
		board.getPiece(Piece(Piece::Type::King, color)).value();
	const auto& king = board.getPiece(kingCoord);

	auto pathDir = [&board, &kingCoord]
	(const eqx::Point<int>& dir)
	{
		return board.walkDir(kingCoord, dir);
	};

	auto checkPiecesFor = []
	(const auto& pieces, const auto& piece)
	{
		return std::ranges::find(pieces, piece) !=
			std::ranges::end(pieces);
	};

	auto checkCoordsFor = [&board, &kingCoord]
	(const auto& rawCoords, const auto& piece)
	{
		auto result = std::ranges::find_if(rawCoords,
			[&board, &piece, &kingCoord]
		(const auto& val)
			{
				auto coord = val + kingCoord;
				if (inBounds(coord) &&
					board.getPiece(coord) == piece)
				{
					return true;
				}
				else
				{
					return false;
				}
			});
		return result != std::ranges::end(rawCoords);
	};

	auto rookThreats = std::array<Piece, 4ULL>({
		pathDir(eqx::Point<int>(0, 1)),
		pathDir(eqx::Point<int>(0, -1)),
		pathDir(eqx::Point<int>(1, 0)),
		pathDir(eqx::Point<int>(-1, 0))
		});

	auto bishopThreats = std::array<Piece, 4ULL>({
		pathDir(eqx::Point<int>(1, 1)),
		pathDir(eqx::Point<int>(1, -1)),
		pathDir(eqx::Point<int>(-1, 1)),
		pathDir(eqx::Point<int>(-1, -1))
		});

	result = result || checkPiecesFor(rookThreats,
		Piece(Piece::Type::Rook, !king.getColor()));
	result = result || checkPiecesFor(bishopThreats,
		Piece(Piece::Type::Bishop, !king.getColor()));
	result = result || checkPiecesFor(rookThreats,
		Piece(Piece::Type::Queen, !king.getColor()));
	result = result || checkPiecesFor(bishopThreats,
		Piece(Piece::Type::Queen, !king.getColor()));

	result = result || checkCoordsFor(Moves::Knight,
		Piece(Piece::Type::Knight, !king.getColor()));
	result = result || checkCoordsFor(Moves::King,
		Piece(Piece::Type::King, !king.getColor()));

	if (king.getColor() == Piece::Color::White)
	{
		result = result || checkCoordsFor(Moves::White::PawnTakes,
			Piece(Piece::Type::Pawn, !king.getColor()));
	}
	else
	{
		result = result || checkCoordsFor(Moves::Black::PawnTakes,
			Piece(Piece::Type::Pawn, !king.getColor()));
	}

	return result;
}

[[nodiscard]] constexpr bool 
	Move::validSlide(const Board& board) const noexcept
{
	if (pathClear(board) &&
		squareTakable(board))
	{
		return true;
	}
	else
	{
		return false;
	}
}

[[nodiscard]] constexpr bool Move::validJump(const Board& board) const noexcept
{
	if (squareTakable(board))
	{
		return true;
	}
	else
	{
		return false;
	}
}

[[nodiscard]] constexpr bool
	Move::validPawnPush(const Board& board) const noexcept
{
	if (board.coordEmpty(m_Dest))
	{
		return true;
	}
	else
	{
		return false;
	}
}

[[nodiscard]] constexpr bool
	Move::validPawnTake(const Board& board) const noexcept
{
	if (squareOpposed(board))
	{
		return true;
	}
	else
	{
		return false;
	}
}

[[nodiscard]] constexpr bool
	Move::validPawnDouble(const Board& board) const noexcept
{
	if (pathClear(board) &&
		board.coordEmpty(m_Dest) &&
		m_Source.y == 1 || m_Source.y == 6)
	{
		return true;
	}
	else
	{
		return false;
	}
}

[[nodiscard]] constexpr bool
	Move::validEnPassant(const Board& board) const noexcept
{
	auto expectedPassingSquare = eqx::Point<int>(
		m_Dest.x,
		m_Source.y);

	if (board.coordEmpty(m_Dest) &&
		board.getInPassingPiece() == expectedPassingSquare)
	{
		return true;
	}
	else
	{
		return false;
	}
}

[[nodiscard]] constexpr bool 
	Move::validCastle(const Board& board) const noexcept
{
	auto castleRook = eqx::Point<int>(0, m_Source.y);
	auto midBoard = Board(board);
	auto midSquare = eqx::Point<int>(3, m_Source.y);
	auto rtc = board.getRTC(board.getTurn()).longCastle;

	if (m_Type == Move::Type::ShortCastle)
	{
		castleRook.x = 7;
		midSquare.x = 5;
		rtc = board.getRTC(board.getTurn()).shortCastle;
	}

	midBoard.movePiece(m_Source, midSquare);

	auto move = Move(m_Source, castleRook, m_Type);

	if (move.pathClear(board) &&
		rtc &&
		!inCheck(board, board.getTurn()) &&
		!inCheck(midBoard, board.getTurn()))
	{
		return true;
	}
	else
	{
		return false;
	}
}
