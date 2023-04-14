#pragma once

#include <vector>
#include <unordered_map>

#include <EquinoxSTD.hpp>

#include "Board.hpp"

struct Move
{
	bool operator== (const Move& other) const
	{
		return source == other.source && dest == other.dest;
	}

	eqx::Point<int> source, dest;
};

namespace std
{
	template<>
	struct hash<Move>
	{
		size_t operator()(const Move& move) const
		{
			return hash<int>()(move.source.x) ^ hash<int>()(move.source.y) ^
				hash<int>()(move.dest.x) ^ hash<int>()(move.dest.y);
		}
	};
}

namespace Analyzer
{
	[[nodiscard]] std::unordered_map<Move, Board> 
		getAllPermutations(const Board& board);

	[[nodiscard]] std::unordered_map<Move, Board>
		getMoves(const Board& board, const eqx::Point<int>& pieceCoord);
}