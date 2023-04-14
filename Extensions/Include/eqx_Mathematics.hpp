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

#include <type_traits>
#include <concepts>
#include <limits>
#include <cmath>

#include "eqx_Misc.hpp"

namespace eqx
{
	/**
	 * @brief Pi Accurate To 36 Decimal Points
	 * @brief T Must Be A Floating Point Type
	 */
	template <std::floating_point T>
	T constexpr pi_t = static_cast<T>(3.141592653589793238462643383279502884L);

	/**
	 * @brief Pi Accurate To Double Precision
	 */
	double constexpr pi = pi_t<double>;

	/**
	 * @brief Type Accurate Zero
	 */
	template <typename T>
	T constexpr zero = static_cast<T>(0);

	/**
	 * @brief Check If Two Integer Types Are Equal
	 * @brief T Must Be An Integer Type
	 *
	 * @param x, y Values To Be Checked
	 *
	 * @returns true If The Values Are Equal
	 */
	template <eqx::integer T>
	[[nodiscard]] constexpr bool equals(T x, T y) noexcept
	{
		return x == y;
	}

	/**
	 * @brief Check If Two Floating Point Types Are Equal Given Some Amount 
	 *		Of Error
	 * @brief T Must Be A Floating Point Type
	 *
	 * @param x, y Values To Be Checked
	 * @param error Amount Of Inaccuracy Permissible
	 *
	 * @returns true If The Difference Is Less Than error
	 */
	template <std::floating_point T>
	[[nodiscard]] bool 
		equals(T x, T y, T error = static_cast<T>(0.001)) noexcept
	{
		return (std::abs(x - y) < error);
	}

	/**
	 * @brief Checks The Sign Of A Given Value
	 * @brief T Must Be An Arithmetic Type
	 * 
	 * @param val To Be Checked
	 * 
	 * @returns 1, 0, And -1 For Positive, Zero, And Negative
	 *		Values Respectively
	 */
	template <eqx::arithmetic T>
	[[nodiscard]] int constexpr getSign(T val) noexcept
	{
		if (val > eqx::zero<T>)
		{
			return 1;
		}
		else if (val < eqx::zero<T>)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}

	/**
	 * @brief Check If A Value Is Positive, Note That 0 Is Not Positive
	 * @brief T Must Be An Arithmetic Type
	 * 
	 * @param val Value To Be Checked
	 * 
	 * @returns true If The Value Is Positive
	 */
	template <eqx::arithmetic T>
	[[nodiscard]] bool constexpr isPositive(T val) noexcept
	{
		if (getSign(val) == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 * @brief Check If A Value Is Negative, Note That 0 Is Not Negative
	 * @brief T Must Be An Arithmetic Type
	 *
	 * @param val Value To Be Checked
	 *
	 * @returns true If The Value Is Negative
	 */
	template <eqx::arithmetic T>
	[[nodiscard]] bool constexpr isNegative(T val) noexcept
	{
		if (getSign(val) == -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 * @brief Check If Two Values Will Overflow By Addition
	 * @brief T Must Be An Arithmetic Type
	 *
	 * @param x, y Values To Be Checked
	 *
	 * @returns true If Overflow Would Occur
	 */
	template <eqx::arithmetic T>
	[[nodiscard]] bool constexpr willOverflowAddition(T x, T y) noexcept
	{
		if (x >= eqx::zero<T> && y >= eqx::zero<T>)
		{
			return (std::numeric_limits<T>::max() - x) < y;
		}
		else if (x <= eqx::zero<T> && y <= eqx::zero<T>)
		{
			return (std::numeric_limits<T>::lowest() - x) > y;
		}
		else
		{
			return false;
		}
	}

	/**
	 * @brief Check If Two Values Will Overflow By Subtraction
	 * @brief T Must Be An Arithmetic Type
	 *
	 * @param x, y Values To Be Checked
	 *
	 * @returns true If Overflow Would Occur
	 */
	template <eqx::signedArithmetic T>
	[[nodiscard]] bool constexpr willOverflowSubtraction(T x, T y) noexcept
	{
		if (y == std::numeric_limits<T>::lowest() && eqx::signedInteger<T>)
		{
			return true;
		}
		else
		{
			return willOverflowAddition(x, -y);
		}
	}

	/**
	 * @brief Check If Two Values Will Overflow By Subtraction
	 * @brief T Must Be An Arithmetic Type
	 *
	 * @param x, y Values To Be Checked
	 *
	 * @returns true If Overflow Would Occur
	 */
	template <eqx::unsignedInteger T>
	[[nodiscard]] bool constexpr willOverflowSubtraction(T x, T y) noexcept
	{
		if (y > x)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 * @brief Compute The Distance Between Two One Dimensional Points
	 * @brief T Must Be An Arithmetic Type
	 * 
	 * @param x1, x2 Values On A One Dimensional Plane
	 *
	 * @returns Distance Between Two One Dimensional Points
	 */
	template <eqx::arithmetic T>
	[[nodiscard]] T distance(T x1, T x2) noexcept
	{
		if (x2 > x1)
		{
			std::swap(x1, x2);
		}

		eqx::runtimeAssert(!willOverflowSubtraction(x1, x2), 
			"Arithmetic Overflow!");

		return static_cast<T>(std::fabs(x1 - x2));
	}

	/**
	 * @brief Convert Degrees To Radians
	 * @brief T Must Be An Arithmetic Type
	 * 
	 * @param degrees Degrees To Be Converted
	 * 
	 * @returns double Equal To The Radian Equivalent Of degrees
	 */
	template <eqx::arithmetic T>
	[[nodiscard]] double constexpr degreesToRadians(T degrees) noexcept
	{
		return static_cast<double>(degrees) * (eqx::pi / 180.0);
	}

	/**
	 * @brief Convert Radians To Degrees
	 * @brief T Must Be An Arithmetic Type
	 *
	 * @param radians Radians To Be Converted
	 *
	 * @returns double Equal To The Degree Equivalent Of radians
	 */
	template <eqx::arithmetic T>
	[[nodiscard]] double constexpr radiansToDegrees(T radians) noexcept
	{
		return static_cast<double>(radians) * (180.0 / eqx::pi);
	}

	/**
	 * @brief Compute Both Arccosine Values
	 * @brief T Must Be An Arithmetic Type
	 * @brief value Must Be In Interval [-1.0, 1.0]
	 *
	 * @param value Value To Be Computed
	 *
	 * @returns std::pair<double, double>, Values Are In Degrees
	 */
	template <eqx::arithmetic T>
	[[nodiscard]] std::pair<double, double> arccos(T value) noexcept
	{
		eqx::runtimeAssert(value >= -1.0 && value <= 1.0, "Domain Error!");

		std::pair<double, double> result;
		result.first = eqx::radiansToDegrees(std::acos(value));
		result.second = 360.0 - result.first;
		return result;
	}

	/**
	 * @brief Compute Both Arcsine Values
	 * @brief T Must Be An Arithmetic Type
	 * @brief value Must Be In Interval [-1.0, 1.0]
	 * 
	 * @param value Value To Be Computed
	 * 
	 * @returns std::pair<double, double>, Values Are In Degrees
	 */
	template <eqx::arithmetic T>
	[[nodiscard]] std::pair<double, double> arcsin(T value) noexcept
	{
		eqx::runtimeAssert(value >= -1.0 && value <= 1.0, "Domain Error!");

		std::pair<double, double> result;
		result.first = eqx::radiansToDegrees(std::asin(value));
		result.second = 180.0 - result.first;
		result.first = result.first >= 0.0 ?
			result.first : 360.0 + result.first;
		return result;
	}
}