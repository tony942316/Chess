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
#include <cmath>
#include <cerrno>

#include "eqx_Misc.hpp"
#include "eqx_Mathematics.hpp"

namespace eqx
{
	/**
	 * @brief Point On The Cartesian Plane i.e. (X, Y), Note T
	 *		Must Be An Arithmetic Type
	 */
	template <eqx::arithmetic T>
	class Point
	{
	public:
		/**
		 * @brief Initialized With Zeros i.e. ((T)0, (T)0)
		 */
		constexpr Point() noexcept
			:
			Point(eqx::zero<T>, eqx::zero<T>)
		{
		}

		/**
		 * @brief Initialize With Values i.e. (x, y)
		 * 
		 * @param x The x Value
		 * @param y The y Value
		 */
		constexpr Point(T x, T y) noexcept
			:
			x(x),
			y(y)
		{
		}

		/**
		 * Trivial Move And Copy Operation
		 */
		Point(const Point& other) = default;
		Point(Point&& other) = default;
		Point& operator= (const Point& other) = default;
		Point& operator= (Point&& other) = default;
		~Point() = default;

		/**
		 * @brief x + other.x, y + other.y
		 * 
		 * @param other The Same Type Point We Add From
		 * 
		 * @returns Resulting Point
		 */
		[[nodiscard]] constexpr 
			Point<T> operator+ (const Point<T>& other) const noexcept
		{
			return Point<T>(x + other.x, y + other.y);
		}

		/**
		 * @brief x - other.x, y - other.y
		 * 
		 * @param other The Same Type Point We Subtract From
		 * 
		 * @returns Resulting Point
		 */
		[[nodiscard]] constexpr 
			Point<T> operator- (const Point<T>& other) const noexcept
		{
			return Point<T>(x - other.x, y - other.y);
		}

		/**
		 * @brief x += other.x, y += other.y
		 * 
		 * @param other The Same Type Point We Add From
		 * 
		 * @returns *this
		 */
		constexpr Point<T> operator+= (const Point<T>& other) noexcept
		{
			return *this = *this + other;
		}

		/**
		 * @brief x -= other.x, y -= other.y
		 *
		 * @param other The Same Type Point We Subtract From
		 * 
		 * @returns *this
		 */
		constexpr Point<T> operator-= (const Point<T>& other) noexcept
		{
			return *this = *this - other;
		}

		/**
		 * @brief eqx::equals(x, other.x), eqx::equals(y, other.y)
		 * 
		 * @param other The Same Type Point We Compare Against
		 * 
		 * @returns true If Points Are Equivalent
		 */
		[[nodiscard]] constexpr 
			bool operator== (const Point<T>& other) const noexcept
		{
			return equals(*this, other);
		}

		/**
		 * @brief !eqx::equals(x, other.x), !eqx::equals(y, other.y)
		 *
		 * @param other The Same Type Point We Compare Against
		 *
		 * @returns true If Points Are Equivalent
		 */
		[[nodiscard]] constexpr 
			bool operator!= (const Point<T>& other) const noexcept
		{
			return !(*this == other);
		}

		/**
		 * @brief Computes The Distance From This Point To other
		 *
		 * @param other Point To Where The Distance Is Calculated
		 *
		 * @returns Distance Between This Point And other
		 */
		[[nodiscard]] T distanceTo(const Point<T>& other) const noexcept
		{
			eqx::runtimeAssert(errno == 0, "Previous errno Failure Detected!");

			auto dx = static_cast<double>(distance(x, other.x));
			auto dy = static_cast<double>(distance(y, other.y));
			auto result = std::hypot(dx, dy);

			eqx::runtimeAssert(errno != ERANGE, "errno == ERANGE!");

			return static_cast<T>(result);
		}

		/**
		 * @brief Creates Printable String Of Form "(x, y)"
		 * 
		 * @returns "(x, y)"
		 */
		[[nodiscard]] std::string toString() const
		{
			auto res = std::string("");
			res += "(";
			res += std::to_string(x);
			res += ", ";
			res += std::to_string(y);
			res += ")";
			return res;
		}

		T x, y;
	};

	/**
	 * @brief Convert An eqx::Point To A std::string Of Form
	 *		"(point.x, point.y)"
	 *
	 * @param point Point To Be Converted
	 *
	 * @returns Point Converted To A std::string
	 */
	template <typename T>
	[[nodiscard]] std::string toString(const Point<T>& point)
	{
		return point.toString();
	}

	/**
	 * @brief point1 == point2
	 *
	 * @param point1 First Point
	 * @param point2 Second Point
	 *
	 * @returns true If Points Are Equivalent
	 */
	template <typename T>
	[[nodiscard]] constexpr 
		bool equals(const Point<T>& point1, const Point<T>& point2,
			double error = 0.001) noexcept
	{
		return equals(point1.x, point2.x, error) && 
			equals(point1.y, point2.y, error);
	}

	/**
	 * @brief Computes The Distance Between Two Points
	 * 
	 * @param point1 First Point
	 * @param point2 Second Point
	 * 
	 * @returns Distance Between The Points
	 */
	template <typename T>
	[[nodiscard]] 
		T distance(const Point<T>& point1, const Point<T>& point2) noexcept
	{
		return point1.distanceTo(point2);
	}

	/**
	 * @brief Normalize A Point As If It Were A Vector From The Origin (0, 0),
	 *		Note T Must Be A std::floating_point
	 * 
	 * @param point Point To Be Normalized
	 * 
	 * @returns Normalized Point
	 */
	template <std::floating_point T>
	[[nodiscard]] Point<T> normalize(const Point<T>& point) noexcept
	{
		constexpr auto origin = Point<T>();

		auto dist = eqx::distance(origin, point);
		eqx::runtimeAssert(dist != eqx::zero<T>, "dist Was 0!");

		auto result = Point<T>(point.x / dist, point.y / dist);
		return result;
	}

	/**
	 * @brief Compute The Angle Of A Point In Degrees, Counter Clockwise
	 *		From The Origin (0, 0)
	 * 
	 * @param point Point The Angle Is Computed From
	 * 
	 * @returns Angle In Degrees
	 */
	template <typename T>
	[[nodiscard]] double angle(const Point<T>& point) noexcept
	{
		auto normPoint = eqx::normalize(point);
		auto sinVals = eqx::arcsin(normPoint.y);
		auto cosVals = eqx::arccos(normPoint.x);

		auto correctValue = equals(sinVals.first, cosVals.first) ||
			equals(sinVals.second, cosVals.second) ?
			sinVals.first : sinVals.second;

		return correctValue;
	}
}