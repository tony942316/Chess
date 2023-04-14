#include "Piece.hpp"

namespace Pieces::White
{
	Piece Rook = Piece(Piece::Type::Rook, Piece::Color::White);
	Piece Knight = Piece(Piece::Type::Knight, Piece::Color::White);
	Piece Bishop = Piece(Piece::Type::Bishop, Piece::Color::White);
	Piece Queen = Piece(Piece::Type::Queen, Piece::Color::White);
	Piece King = Piece(Piece::Type::King, Piece::Color::White);
	Piece Pawn = Piece(Piece::Type::Pawn, Piece::Color::White);
}

namespace Pieces::Black
{
	Piece Rook = Piece(Piece::Type::Rook, Piece::Color::Black);
	Piece Knight = Piece(Piece::Type::Knight, Piece::Color::Black);
	Piece Bishop = Piece(Piece::Type::Bishop, Piece::Color::Black);
	Piece Queen = Piece(Piece::Type::Queen, Piece::Color::Black);
	Piece King = Piece(Piece::Type::King, Piece::Color::Black);
	Piece Pawn = Piece(Piece::Type::Pawn, Piece::Color::Black);
}

Piece::Piece()
	:
	m_Type(Type::None),
	m_Color(Color::None)
{
}

Piece::Piece(Type type, Color color)
	:
	m_Type(type),
	m_Color(color)
{
}

bool Piece::operator== (const Piece& other) const
{
	return m_Type == other.m_Type && m_Color == other.m_Color;
}

Piece::Type Piece::getType() const
{
	return m_Type;
}

Piece::Color Piece::getColor() const
{
	return m_Color;
}
