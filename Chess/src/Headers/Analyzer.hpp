#pragma once

#include <memory>

#include <vector>
#include <unordered_map>

#include <EquinoxSTD.hpp>

#include "Board.hpp"
#include "Move.hpp"

namespace Analyzer
{
	[[nodiscard]] std::unordered_map<Move, Board> 
		getAllPermutations(const Board& board)
	{
		board;
		return std::unordered_map<Move, Board>();
	}

	[[nodiscard]] std::vector<Move> getMoves(const Board& board,
		const eqx::Point<int>& pieceCoord)
	{
		board;
		pieceCoord;
		return std::vector<Move>();
	}
}