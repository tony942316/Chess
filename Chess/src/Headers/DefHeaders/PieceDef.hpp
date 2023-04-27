#pragma once

constexpr Piece::Piece() noexcept
	:
	m_Type(Type::None),
	m_Color(Color::None)
{
}

constexpr Piece::Piece(Type type, Color color) noexcept
	:
	m_Type(type),
	m_Color(color)
{
}

[[nodiscard]] constexpr bool
	Piece::operator== (const Piece& other) const noexcept
{
	return m_Type == other.m_Type && m_Color == other.m_Color;
}

[[nodiscard]] constexpr Piece::Type Piece::getType() const noexcept
{
	return m_Type;
}

[[nodiscard]] constexpr Piece::Color Piece::getColor() const noexcept
{
	return m_Color;
}

[[nodiscard]] constexpr Piece::Color operator! (Piece::Color color) noexcept
{
	switch (color)
	{
	case Piece::Color::White:
		return Piece::Color::Black;
		break;
	case Piece::Color::Black:
		return Piece::Color::White;
		break;
	case Piece::Color::None:
		return Piece::Color::None;
		break;
	default:
		return Piece::Color::None;
		break;
	}
}
