/*
 * Copyright (C) 2023 Anthony H. Grasso
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <string>

#include "eqx_Misc.hpp"
#include "eqx_Point.hpp"
#include "eqx_Mathematics.hpp"

namespace eqx
{
	/**
	 * @brief Rectangle On The Cartesian Plane Stored As Top Left Coordinates
	 *		X, Y And Width And Height, Note That The Rectangle Coordinates
	 *		Act As If They Are In Screen Space i.e. The Height Of The
	 *		Rectangle Is Directed Downwards
	 */
	template<eqx::arithmetic T>
	class Rectangle
	{
	public:
		/**
		 * @brief Initialized With Zeros i.e. ((T)0, ...)
		 */
		constexpr Rectangle() noexcept
			:
			Rectangle(eqx::zero<T>, eqx::zero<T>, eqx::zero<T>, eqx::zero<T>)
		{
		}

		/**
		 * @brief Initalize With Values i.e. (x, y, w, h)
		 * 
		 * @param x The x Value
		 * @param y The y Value
		 * @param w The Width
		 * @param h The Height
		 */
		constexpr Rectangle(T x, T y, T w, T h) noexcept
			:
			x(x),
			y(y),
			w(w),
			h(h)
		{
		}

		/**
		 * Trivial Move And Copy Operation
		 */
		Rectangle(const Rectangle& other) = default;
		Rectangle(Rectangle&& other) = default;
		Rectangle& operator= (const Rectangle& other) = default;
		Rectangle& operator= (Rectangle&& other) = default;
		~Rectangle() = default;

		/**
		 * @brief Create A Point At (X, Y), Note That This Is An
		 *		Alias For GetTopLeftPoint()
		 * 
		 * @returns eqx::Point<T> Representing The Top Left Point
		 */
		[[nodiscard]] constexpr eqx::Point<T> getLocation() const noexcept
		{
			return getTopLeftPoint();
		}

		/**
		 * @brief Create A Point At (X, Y), The Top Left Point
		 * 
		 * @returns eqx::Point<T> Representing The Top Left Point
		 */
		[[nodiscard]] constexpr eqx::Point<T> getTopLeftPoint() const noexcept
		{
			return eqx::Point<T>(x, y);
		}

		/**
		 * @brief Create A Point At (X + W, Y), The Top Right Point
		 * 
		 * @returns eqx::Point<T> Representing The Top Right Point
		 */
		[[nodiscard]] constexpr eqx::Point<T> getTopRightPoint() const noexcept
		{
			return eqx::Point<T>(x + w, y);
		}

		/**
		 * @brief Create A Point At (X, Y + H), The Bottom Left Point
		 * 
		 * @returns eqx::Point<T> Representing The Bottom Left Point
		 */
		[[nodiscard]] constexpr 
			eqx::Point<T> getBottomLeftPoint() const noexcept
		{
			return eqx::Point<T>(x, y + h);
		}

		/**
		 * @brief Create A Point At (X + W, Y + H), The Bottom Right Point
		 * 
		 * @returns eqx::Point<T> Representing The Bottom Right Point
		 */
		[[nodiscard]] constexpr 
			eqx::Point<T> getBottomRightPoint() const noexcept
		{
			return eqx::Point<T>(x + w, y + h);
		}

		/**
		 * @brief Create A Point At (X + 0.5 * W, Y + 0.5 * H), 
		 *		The Center point
		 * 
		 * @returns eqx::Point<T> Representing The Center Point
		 */
		[[nodiscard]] constexpr eqx::Point<T> getCenterPoint() const noexcept
		{
			auto dx = static_cast<T>(w * 0.5);
			auto dy = static_cast<T>(h * 0.5);
			return eqx::Point<T>(x + dx, y + dy);
		}

		/**
		 * @brief Creates Printable String Of Form "(x, y, w, h)"
		 * 
		 * @returns "(x, y, w, h)"
		 */
		[[nodiscard]] std::string toString() const
		{
			auto res = std::string("");
			res += "(";
			res += std::to_string(x);
			res += ", ";
			res += std::to_string(y);
			res += ", ";
			res += std::to_string(w);
			res += ", ";
			res += std::to_string(h);
			res += ")";
			return res;
		}

		T x, y, w, h;
	};

	/**
	 * @brief Convert An eqx::Rectangle To A std::string Of Form
	 *		"(rect.x, rect.y, rect.w, rect.h)"
	 *
	 * @param rect Rectangle To Be Converted
	 *
	 * @returns Rectangle Converted To A std::string
	 */
	template <typename T>
	[[nodiscard]] std::string toString(const eqx::Rectangle<T>& rect)
	{
		return rect.toString();
	}

	/**
	 * @brief Determine If A Point Is Contained Inside A Rectangle
	 * 
	 * @param rect The Rectangle
	 * @param point The Point
	 * 
	 * @returns true If point Is Contained By rect
	 */
	template <typename T>
	[[nodiscard]] constexpr bool 
		intersect(const Rectangle<T>& rect, const Point<T>& point) noexcept
	{
		if (point.x < rect.getTopLeftPoint().x ||
			point.x > rect.getTopRightPoint().x ||
			point.y > rect.getBottomLeftPoint().y ||
			point.y < rect.getTopLeftPoint().y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	/**
	 * @brief Determine If Two Rectangles Overlap
	 * 
	 * @param rect1 The First Rectangle
	 * @param rect2 The Second Rectangle
	 * 
	 * @returns true If There Is Any Overlap Between rect1 And rect2
	 */
	template <typename T>
	[[nodiscard]] constexpr bool intersect(const Rectangle<T>& rect1, 
		const Rectangle<T>& rect2) noexcept
	{
		if (rect1.getBottomRightPoint().x < rect2.getBottomLeftPoint().x ||
			rect1.getBottomLeftPoint().x > rect2.getBottomRightPoint().x ||
			rect1.getBottomLeftPoint().y < rect2.getTopLeftPoint().y ||
			rect1.getTopLeftPoint().y > rect2.getBottomLeftPoint().y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}