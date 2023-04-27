#pragma once

#include <optional>

#include <array>

#include <EquinoxSTD.hpp>

#include "Piece.hpp"

[[nodiscard]] constexpr bool inBounds(const eqx::Point<int>& coord) noexcept;

[[nodiscard]] constexpr int 
	coordToIndex(const eqx::Point<int>& coord) noexcept;

[[nodiscard]] constexpr eqx::Point<int> indexToCoord(int index) noexcept;

class Board
{
public:
	struct RTC
	{
		bool longCastle, shortCastle;
	};

	explicit constexpr Board() noexcept;

	[[nodiscard]] constexpr const Piece&
		getPiece(const eqx::Point<int>& coord) const noexcept;

	[[nodiscard]] constexpr std::optional<eqx::Point<int>>
		getPiece(const Piece& piece) const noexcept;

	[[nodiscard]] constexpr const Piece& walkDir(const eqx::Point<int>& coord,
		const eqx::Point<int>& dir) const noexcept;

	[[nodiscard]] constexpr bool
		coordEmpty(const eqx::Point<int>& coord) const noexcept;

	constexpr void movePiece(const eqx::Point<int>& pieceCoord,
		const eqx::Point<int>& destCoord) noexcept;

	constexpr void removePiece(const eqx::Point<int>& pieceCoord) noexcept;

	constexpr void setInPassingPiece(const eqx::Point<int>& coord) noexcept;

	constexpr void setTurn(Piece::Color color) noexcept;

	[[nodiscard]] constexpr RTC& editRTC(Piece::Color color) noexcept;

	[[nodiscard]] constexpr const std::array<Piece, 64ULL>&
		getBoard() const noexcept;

	[[nodiscard]] constexpr const RTC&
		getRTC(Piece::Color color) const noexcept;

	[[nodiscard]] constexpr const eqx::Point<int>&
		getInPassingPiece() const noexcept;

	[[nodiscard]] constexpr Piece::Color getTurn() const noexcept;

private:
	std::array<Piece, 64ULL> m_Board;
	RTC m_WhiteRTC, m_BlackRTC;
	eqx::Point<int> m_InPassingPiece;
	Piece::Color m_Turn;
};

#include "DefHeaders/BoardDef.hpp"
