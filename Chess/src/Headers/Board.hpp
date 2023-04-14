#pragma once

#include <EquinoxSTD.hpp>

#include <array>
#include <vector>

#include "Piece.hpp"

class Board
{
public:
	struct RTC
	{
		bool longCastle, shortCastle;
	};

	Board();

	[[nodiscard]] const Piece& getPiece(const eqx::Point<int>& coord) const;
	[[nodiscard]] std::vector<eqx::Point<int>> getAllPieces() const;
	void movePiece(const eqx::Point<int>& pieceCoord, 
		const eqx::Point<int>& destCoord);

	[[nodiscard]] const RTC& getRTC(Piece::Color color) const noexcept;
	[[nodiscard]] RTC& editRTC(Piece::Color color) noexcept;

	[[nodiscard]] const std::array<Piece, 64ULL>& getBoard() const noexcept;

	[[nodiscard]] const eqx::Point<int>& getInPassingPiece() const noexcept;
	void setInPassingPiece(const eqx::Point<int>& coord) noexcept;

	[[nodiscard]] Piece::Color getTurn() const noexcept;
	void setTurn(Piece::Color color) noexcept;

private:
	[[nodiscard]] constexpr int
		coordToIndex(const eqx::Point<int>& coord) const noexcept;
	[[nodiscard]] constexpr eqx::Point<int>
		indexToCoord(int index) const noexcept;

	std::array<Piece, 64ULL> m_Board;
	RTC m_WhiteRTC, m_BlackRTC;
	eqx::Point<int> m_InPassingPiece;
	Piece::Color m_Turn;
};