#pragma once

#include <EquinoxSTD.hpp>

#include "Board.hpp"

namespace Moves
{
	inline constexpr auto Knight = std::array<eqx::Point<int>, 8ULL>({
		eqx::Point<int>(1, 2),
		eqx::Point<int>(1, -2),
		eqx::Point<int>(-1, 2),
		eqx::Point<int>(-1, -2),
		eqx::Point<int>(2, 1),
		eqx::Point<int>(2, -1),
		eqx::Point<int>(-2, 1),
		eqx::Point<int>(-2, -1)
	});

	inline constexpr auto King = std::array<eqx::Point<int>, 8ULL>({
		eqx::Point<int>(0, 1),
		eqx::Point<int>(0, -1),
		eqx::Point<int>(1, 0),
		eqx::Point<int>(-1, 0),
		eqx::Point<int>(1, 1),
		eqx::Point<int>(1, -1),
		eqx::Point<int>(-1, 1),
		eqx::Point<int>(-1, -1)
	});

	inline constexpr auto Castle = std::array<eqx::Point<int>, 2ULL>({
		eqx::Point<int>(2, 0),
		eqx::Point<int>(-2, 0)
	});

	namespace White
	{
		inline constexpr auto PawnTakes = std::array<eqx::Point<int>, 2ULL>({
			eqx::Point<int>(1, -1),
			eqx::Point<int>(-1, -1)
		});

		inline constexpr auto PawnMoves = std::array<eqx::Point<int>, 2ULL>({
			eqx::Point<int>(0, -1),
			eqx::Point<int>(0, -2)
		});
	}

	namespace Black
	{
		inline constexpr auto PawnTakes = std::array<eqx::Point<int>, 2ULL>({
			eqx::Point<int>(1, 1),
			eqx::Point<int>(-1, 1)
		});

		inline constexpr auto PawnMoves = std::array<eqx::Point<int>, 2ULL>({
			eqx::Point<int>(0, 1),
			eqx::Point<int>(0, 2)
		});
	}
}

class Move
{
public:
	enum class Type
	{
		Slide,
		Jump,
		PawnPush,
		PawnTake,
		PawnDouble,
		EnPassant,
		LongCastle,
		ShortCastle,
		None
	};

	explicit constexpr Move() noexcept;

	explicit constexpr Move(const eqx::Point<int>& source,
		const eqx::Point<int>& dest, Type type) noexcept;

	[[nodiscard]] constexpr bool operator== (const Move& other) const noexcept;

	[[nodiscard]] constexpr bool isValid(const Board& board) const;

	[[nodiscard]] constexpr Board apply(const Board& board) const noexcept;

	constexpr void setSource(const eqx::Point<int>& source) noexcept;

	constexpr void setDest(const eqx::Point<int>& dest) noexcept;

	constexpr void setType(Type type) noexcept;
	
	[[nodiscard]] constexpr const eqx::Point<int>& getSource() const noexcept;

	[[nodiscard]] constexpr const eqx::Point<int>& getDest() const noexcept;

	[[nodiscard]] constexpr Type getType() const noexcept;

private:
	[[nodiscard]] constexpr bool pathClear(const Board& board) const noexcept;

	[[nodiscard]] constexpr bool
		squareOpposed(const Board& board) const noexcept;

	[[nodiscard]] constexpr bool
		squareTakable(const Board& board) const noexcept;

	[[nodiscard]] static constexpr bool
		inCheck(const Board& board, Piece::Color color);

	[[nodiscard]] constexpr bool validSlide(const Board& board) const noexcept;

	[[nodiscard]] constexpr bool validJump(const Board& board) const noexcept;

	[[nodiscard]] constexpr bool
		validPawnPush(const Board& board) const noexcept;

	[[nodiscard]] constexpr bool
		validPawnTake(const Board& board) const noexcept;

	[[nodiscard]] constexpr bool
		validPawnDouble(const Board& board) const noexcept;

	[[nodiscard]] constexpr bool
		validEnPassant(const Board& board) const noexcept;

	[[nodiscard]] constexpr bool 
		validCastle(const Board& board) const noexcept;

	eqx::Point<int> m_Source, m_Dest;
	Type m_Type;
};

[[nodiscard]] constexpr bool inBounds(const Move& move) noexcept;

template<>
struct std::hash<Move>
{
	[[nodiscard]] std::size_t operator()(const Move& move) const noexcept
	{
		return std::hash<eqx::Point<int>>()(move.getSource()) ^
			std::hash<eqx::Point<int>>()(move.getDest()) ^
			std::hash<Move::Type>()(move.getType());
	}
};

#include "DefHeaders/MoveDef.hpp"
