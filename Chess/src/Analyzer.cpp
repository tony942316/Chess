#include "Analyzer.hpp"

#include "Piece.hpp"

#include <algorithm>

namespace Analyzer
{
	std::unordered_map<Move, Board> getAllPermutations(const Board& board)
	{
		auto result = std::unordered_map<Move, Board>();
		result.reserve(256ULL);
		auto allPieces = board.getAllPieces();
		
		std::ranges::for_each(allPieces,
			[&board, &result](const auto& piece)
			{
				auto moves = getMoves(board, piece);
				std::ranges::for_each(moves,
					[&result](const auto& p)
					{
						result[p.first] = p.second;
					});
			});

		return result;
	}

	std::unordered_map<Move, Board> getMoves(const Board& board,
		const eqx::Point<int>& pieceCoord)
	{
		auto result = std::unordered_map<Move, Board>();
		result.reserve(32ULL);
		auto rawMoves = std::vector<eqx::Point<int>>();
		rawMoves.reserve(32ULL);
		const auto& piece = board.getPiece(pieceCoord);

		auto inBounds = [](const eqx::Point<int>& coord)
		{
			return eqx::intersect(eqx::Rectangle<int>(0, 0, 7, 7), coord);
		};

		auto fillDir = [&](const eqx::Point<int>& dir)
		{
			auto cur = pieceCoord + dir;
			while (inBounds(cur))
			{
				if (board.getPiece(cur).getColor() == piece.getColor())
				{
					break;
				}
				else if (board.getPiece(cur).getColor() != Piece::Color::None)
				{
					rawMoves.emplace_back(cur);
					break;
				}
				rawMoves.emplace_back(cur);
				cur += dir;
			}
		};

		switch (piece.getType())
		{
		case Piece::Type::Rook:
			fillDir({ 1, 0 });
			fillDir({ -1, 0 });
			fillDir({ 0, 1 });
			fillDir({ 0, -1 });
			break;
		case Piece::Type::Knight:
			break;
		case Piece::Type::Bishop:
			break;
		case Piece::Type::Queen:
			break;
		case Piece::Type::King:
			break;
		case Piece::Type::Pawn:
			break;
		}

		std::ranges::for_each(rawMoves,
			[&](const auto& val)
			{
				auto move = Move({ pieceCoord, val });
				auto newPermutation = Board(board);
				newPermutation.movePiece(pieceCoord, val);
				// Deal with Special Cases...
				result.emplace(move, newPermutation);
			});
		

		return result;
	}

	//[[nodiscard]] std::vector<eqx::Point<int>>
	//	getMoves(const Board& board, const eqx::Point<int>& pieceCoord)
	//{
	//	auto possibleResults = std::vector<eqx::Point<int>>();
	//	possibleResults.reserve(32ULL);
	//	auto results = std::vector<eqx::Point<int>>();
	//	results.reserve(32ULL);
	//	auto& piece = board.getPiece(pieceCoord);

	//	auto pointInBounds = [](const eqx::Point<int>& coord)
	//	{
	//		return eqx::intersect(eqx::Rectangle<int>(0, 0, 7, 7), coord);
	//	};

	//	auto fillDir = [&](const eqx::Point<int>& dir)
	//	{
	//		auto cur = pieceCoord + dir;
	//		while (pointInBounds(cur))
	//		{
	//			if (board.getPiece(cur).getColor() == piece.getColor())
	//			{
	//				break;
	//			}
	//			else if (board.getPiece(cur).getColor() != Piece::Color::None)
	//			{
	//				possibleResults.emplace_back(cur);
	//				break;
	//			}
	//			possibleResults.emplace_back(cur);
	//			cur += dir;
	//		}
	//	};

	//	auto knightMoves = [&]()
	//	{
	//		auto validCoords = std::array<eqx::Point<int>, 8ULL>({
	//			{ 1, 2 },
	//			{ 1, -2 },
	//			{ -1, 2 },
	//			{ -1, -2 },
	//			{ 2, 1 },
	//			{ 2, -1 },
	//			{ -2, 1 },
	//			{ -2, -1 }
	//		});
	//		std::ranges::for_each(validCoords,
	//			[&](const auto& val)
	//			{
	//				auto cur = pieceCoord + val;
	//				if (pointInBounds(cur) &&
	//					board.getPiece(cur).getColor() != piece.getColor())
	//				{
	//					possibleResults.emplace_back(cur);
	//				}
	//			});
	//	};

	//	auto whitePawnMoves = [&]()
	//	{
	//		auto pushCoord = pieceCoord + eqx::Point<int>({ 0, -1 });
	//		auto firstMoveCoord = pieceCoord + eqx::Point<int>({ 0, -2 });
	//		auto takeCoordLeft = pieceCoord + eqx::Point<int>({ -1, -1 });
	//		auto takeCoordRight = pieceCoord + eqx::Point<int>({ 1, -1 });

	//		if (board.getPiece(pushCoord).getType() == Piece::Type::None)
	//		{
	//			possibleResults.emplace_back(pushCoord);
	//			if (board.getPiece(firstMoveCoord).getType() ==
	//					Piece::Type::None &&
	//				pieceCoord.y == 6)
	//			{
	//				possibleResults.emplace_back(firstMoveCoord);
	//			}
	//		}

	//		if (board.getPiece(takeCoordLeft).getColor() != piece.getColor() &&
	//			board.getPiece(takeCoordLeft).getColor() != Piece::Color::None)
	//		{
	//			possibleResults.emplace_back(takeCoordLeft);
	//		}

	//		if (board.getPiece(takeCoordRight).getColor() != 
	//				piece.getColor() &&
	//			board.getPiece(takeCoordRight).getColor() != 
	//				Piece::Color::None)
	//		{
	//			possibleResults.emplace_back(takeCoordRight);
	//		}
	//	};

	//	auto blackPawnMoves = [&]()
	//	{
	//		auto pushCoord = pieceCoord + eqx::Point<int>({ 0, 1 });
	//		auto firstMoveCoord = pieceCoord + eqx::Point<int>({ 0, 2 });
	//		auto takeCoordLeft = pieceCoord + eqx::Point<int>({ -1, 1 });
	//		auto takeCoordRight = pieceCoord + eqx::Point<int>({ 1, 1 });

	//		if (board.getPiece(pushCoord).getType() == Piece::Type::None)
	//		{
	//			possibleResults.emplace_back(pushCoord);
	//			if (board.getPiece(firstMoveCoord).getType() ==
	//				Piece::Type::None &&
	//				pieceCoord.y == 1)
	//			{
	//				possibleResults.emplace_back(firstMoveCoord);
	//			}
	//		}

	//		if (board.getPiece(takeCoordLeft).getColor() != piece.getColor() &&
	//			board.getPiece(takeCoordLeft).getColor() != Piece::Color::None)
	//		{
	//			possibleResults.emplace_back(takeCoordLeft);
	//		}

	//		if (board.getPiece(takeCoordRight).getColor() !=
	//			piece.getColor() &&
	//			board.getPiece(takeCoordRight).getColor() !=
	//			Piece::Color::None)
	//		{
	//			possibleResults.emplace_back(takeCoordRight);
	//		}
	//	};

	//	auto kingMoves = [&]()
	//	{

	//	};

	//	switch (piece.getType())
	//	{
	//	case Piece::Type::Rook:
	//		fillDir({ 1, 0 });
	//		fillDir({ -1, 0 });
	//		fillDir({ 0, 1 });
	//		fillDir({ 0, -1 });
	//		break;
	//	case Piece::Type::Knight:
	//		knightMoves();
	//		break;
	//	case Piece::Type::Bishop:
	//		fillDir({ 1, 1 });
	//		fillDir({ -1, -1 });
	//		fillDir({ 1, -1 });
	//		fillDir({ -1, 1 });
	//		break;
	//	case Piece::Type::Queen:
	//		fillDir({ 1, 1 });
	//		fillDir({ -1, -1 });
	//		fillDir({ 1, -1 });
	//		fillDir({ -1, 1 });
	//		fillDir({ 1, 0 });
	//		fillDir({ -1, 0 });
	//		fillDir({ 0, 1 });
	//		fillDir({ 0, -1 });
	//		break;
	//	case Piece::Type::King:
	//		kingMoves();
	//		break;
	//	case Piece::Type::Pawn:
	//		if (piece.getColor() == Piece::Color::White)
	//		{
	//			whitePawnMoves();
	//		}
	//		else if (piece.getColor() == Piece::Color::Black)
	//		{
	//			blackPawnMoves();
	//		}
	//		break;
	//	default:
	//		break;
	//	}

	//	results = possibleResults;
	//	return results;
	//}
}