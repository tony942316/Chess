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

	Piece();
	Piece(Type type, Color color);

	bool operator== (const Piece& other) const;

	[[nodiscard]] Type getType() const;
	[[nodiscard]] Color getColor() const;

private:
	Type m_Type;
	Color m_Color;
};

namespace std
{
	template<>
	struct hash<Piece>
	{
		size_t operator()(const Piece& piece) const
		{
			return hash<int>()(static_cast<int>(piece.getColor())) ^
				hash<int>()(static_cast<int>(piece.getType()));
		}
	};
}

namespace Pieces::White
{
	extern Piece Rook;
	extern Piece Knight;
	extern Piece Bishop;
	extern Piece Queen;
	extern Piece King;
	extern Piece Pawn;
}

namespace Pieces::Black
{
	extern Piece Rook;
	extern Piece Knight;
	extern Piece Bishop;
	extern Piece Queen;
	extern Piece King;
	extern Piece Pawn;
}