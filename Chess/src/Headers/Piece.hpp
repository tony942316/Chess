#pragma once

#include <functional>

class Piece
{
public:
	enum class Type
	{
		Rook,
		Knight,
		Bishop,
		Queen,
		King,
		Pawn,
		None
	};

	enum class Color
	{
		White,
		Black,
		None
	};

	explicit constexpr Piece() noexcept;
	explicit constexpr Piece(Type type, Color color) noexcept;

	[[nodiscard]] constexpr bool
		operator== (const Piece& other) const noexcept;

	[[nodiscard]] constexpr Type getType() const noexcept;
	[[nodiscard]] constexpr Color getColor() const noexcept;

private:
	Type m_Type;
	Color m_Color;
};

[[nodiscard]] constexpr Piece::Color operator! (Piece::Color color) noexcept;

template<>
struct std::hash<Piece>
{
	[[nodiscard]] std::size_t operator()(const Piece& piece) const noexcept
	{
		return std::hash<Piece::Type>()(piece.getType()) ^
			std::hash<Piece::Color>()(piece.getColor());
	}
};

#include "DefHeaders/PieceDef.hpp"

namespace Pieces::White
{
	inline constexpr auto Rook =
		Piece(Piece::Type::Rook, Piece::Color::White);
	inline constexpr auto Knight =
		Piece(Piece::Type::Knight, Piece::Color::White);
	inline constexpr auto Bishop =
		Piece(Piece::Type::Bishop, Piece::Color::White);
	inline constexpr auto Queen =
		Piece(Piece::Type::Queen, Piece::Color::White);
	inline constexpr auto King =
		Piece(Piece::Type::King, Piece::Color::White);
	inline constexpr auto Pawn =
		Piece(Piece::Type::Pawn, Piece::Color::White);
}

namespace Pieces::Black
{
	inline constexpr auto Rook =
		Piece(Piece::Type::Rook, Piece::Color::Black);
	inline constexpr auto Knight =
		Piece(Piece::Type::Knight, Piece::Color::Black);
	inline constexpr auto Bishop =
		Piece(Piece::Type::Bishop, Piece::Color::Black);
	inline constexpr auto Queen =
		Piece(Piece::Type::Queen, Piece::Color::Black);
	inline constexpr auto King =
		Piece(Piece::Type::King, Piece::Color::Black);
	inline constexpr auto Pawn =
		Piece(Piece::Type::Pawn, Piece::Color::Black);
}
