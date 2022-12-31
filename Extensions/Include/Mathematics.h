#pragma once

#include <type_traits>
#include <limits>

#include "Log.h"

namespace eqx
{
	/**
	 * @brief Long Double Pi Accurate To 36 Decimal Points
	 */
	long double constexpr pi = 3.141592653589793238462643383279502884L;

	/**
	 * @brief x == y UNLESS FLOATING POINT
	 * @brief If Floating Point, Difference Must Be Less Than error
	 *
	 * @param x First Value
	 * @param y Second Value
	 * @param error Amount Of Inaccuracy Permissible For Floating Point Types
	 *
	 * @returns True If Values Are Equivalent
	 */
	template <typename T>
	bool equals(T x, T y, double error = 0.001)
	{
		if (!std::is_arithmetic<T>::value)
		{
			eqx::Log::log(eqx::Log::Level::error, "Not defined for non arithmetic types", eqx::Log::Type::runtimeError);
			return false;
		}
		else if (std::is_integral<T>::value)
		{
			return x == y;
		}
		else if (std::is_floating_point<T>::value)
		{
			return std::fabs(x - y) < static_cast<T>(error);
		}
	}

	/**
	 * @brief Check If Two Aritmetic Types Will Overflow
	 *
	 * @param x Value To Be Checked
	 * @param y Other Value To Be Checked
	 *
	 * @returns True If Overflow Would Occur
	 */
	template<typename T>
	bool willOverflowAddition(T x, T y)
	{
		T zero = static_cast<T>(0);
		if (!std::is_arithmetic<T>::value)
		{
			eqx::Log::log(eqx::Log::Level::error, "Not defined for non arithmetic types", eqx::Log::Type::runtimeError);
			return true;
		}
		else if (x == zero || y == zero)
		{
			return false;
		}
		else if (x > zero && y > zero)
		{
			if ((std::numeric_limits<T>::max() - x) < y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (x < zero && y < zero)
		{
			if ((std::numeric_limits<T>::lowest() - x) > y)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (x > zero && y < zero ||
				 x < zero && y > zero)
		{
			return false;
		}
		else
		{
			eqx::Log::log(eqx::Log::Level::error, "willOverflowAdditionIntegral should not have reached this line", eqx::Log::Type::unreachableCodeError);
			return true;
		}
	}

	/**
	 * @brief Compute The Distance Between Two One Dimensional Points
	 * @brief Must Be Arithmetic Types
	 * 
	 * @param x1 First Point
	 * @param x2 Second Point
	 *
	 * @returns Distance Between Two One Dimensional Points
	 */
	template<typename T>
	T distance(T x1, T x2)
	{
		if (!std::is_arithmetic<T>::value)
		{
			eqx::Log::log(eqx::Log::Level::error, "Not defined for non arithmetic types", eqx::Log::Type::runtimeError);
			return static_cast<T>(0);
		}
		else if (willOverflowAddition(x1, -x2) ||
				 std::is_integral<T>::value && (x1 - x2) == std::numeric_limits<T>::lowest())
		{
			eqx::Log::log(eqx::Log::Level::error, "Arithmetic Overflow", eqx::Log::Type::overflowError);
			return static_cast<T>(0);
		}
		else if (std::is_integral<T>::value)
		{
			return static_cast<T>(std::abs(x1 - x2));
		}
		else if (std::is_floating_point<T>::value)
		{
			return static_cast<T>(std::fabs(x1 - x2));
		}
		else
		{
			eqx::Log::log(eqx::Log::Level::error, "Unknown Case", eqx::Log::Type::runtimeError);
			return static_cast<T>(0);
		}
	}

	/**
	 * @brief Convert Degrees To Radians
	 * 
	 * @param degrees Degrees To Be Converted
	 * 
	 * @returns Radian Equivalent Of The Input
	 */
	template <typename T>
	double degreesToRadians(T degrees)
	{
		return static_cast<double>(degrees) * (static_cast<double>(eqx::pi) / 180.0);
	}

	/**
	 * @brief Convert Radians To Degrees
	 *
	 * @param radians Radians To Be Converted
	 *
	 * @returns Degree Equivalent Of The Input
	 */
	template <typename T>
	double radiansToDegrees(T radians)
	{
		return static_cast<double>(radians) * (180.0 / static_cast<double>(eqx::pi));
	}

	/**
	 * @brief Compute Both Arcsine Values
	 * @brief Value Must Be In Interval [-1.0, 1.0]
	 * 
	 * @param value Value To Be Computed
	 * 
	 * @returns A Pair Of Both Values In Degrees
	 */
	template <typename T>
	std::pair<double, double> arcsin(T value)
	{
		if (value > 1.0 || value < -1.0)
		{
			eqx::Log::log(eqx::Log::Level::error, "Domain Error: [-1.0, 1.0]", eqx::Log::Type::runtimeError);
			return std::make_pair(0.0, 0.0);
		}
		else if (!std::is_arithmetic<T>::value)
		{
			eqx::Log::log(eqx::Log::Level::error, "Not defined for non arithmetic types", eqx::Log::Type::runtimeError);
			return std::make_pair(0.0, 0.0);
		}

		std::pair<double, double> result;
		result.first = eqx::radiansToDegrees(std::asin(value));
		result.second = 180.0 - result.first;
		result.first = result.first >= 0.0 ?
			result.first : 360.0 + result.first;
		return result;
	}

	/**
	 * @brief Compute Both Arccosine Values
	 * @brief Value Must Be In Interval [-1.0, 1.0]
	 *
	 * @param value Value To Be Computed
	 *
	 * @returns A Pair Of Both Values In Degrees
	 */
	template <typename T>
	std::pair<double, double> arccos(T value)
	{
		if (value > 1.0 || value < -1.0)
		{
			eqx::Log::log(eqx::Log::Level::error, "Domain Error: [-1.0, 1.0]", eqx::Log::Type::runtimeError);
			return std::make_pair(0.0, 0.0);
		}
		else if (!std::is_arithmetic<T>::value)
		{
			eqx::Log::log(eqx::Log::Level::error, "Not defined for non arithmetic types", eqx::Log::Type::runtimeError);
			return std::make_pair(0.0, 0.0);
		}

		std::pair<double, double> result;
		result.first = eqx::radiansToDegrees(std::acos(value));
		result.second = 360.0 - result.first;
		return result;
	}
}