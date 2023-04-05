#pragma once

#include <array>

class Board
{
public:
	Board();

	const std::array<char, 64ULL>& getBoard() const;

private:
	std::array<char, 64ULL> m_Board;
};