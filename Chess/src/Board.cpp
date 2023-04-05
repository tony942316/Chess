#include "Board.hpp"

Board::Board()
	:
	m_Board({ 
		'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
		'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
		'-', '-', '-', '-', '-', '-', '-', '-',
		'-', '-', '-', '-', '-', '-', '-', '-',
		'-', '-', '-', '-', '-', '-', '-', '-',
		'-', '-', '-', '-', '-', '-', '-', '-',
		'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
		'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'
	})
{
}

const std::array<char, 64ULL>& Board::getBoard() const
{
	return m_Board;
}
