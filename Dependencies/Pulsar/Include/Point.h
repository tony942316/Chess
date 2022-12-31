#pragma once

#include <type_traits>
#include <limits>
#include <string>
#include <cmath>
#include <cerrno>

#include "Log.h"
#include "Mathematics.h"

namespace eqx
{
	/**
	 * @brief Point On The Cartesian Plane i.e. (X, Y)
	 * @brief Must Be Arithmetic Type
	 */
	template <class T>
	class Point
	{
	public:
		/**
		 * @brief Initialized With A Type Accurate Zero
		 */
		Point()
			:
			Point(static_cast<T>(0), static_cast<T>(0))
		{
		}

		/**
		 * @brief Initialize With Values
		 * 
		 * @param x The x Value
		 * @param y The y Value
		 */
		Point(T x, T y)
			:
			x(x),
			y(y)
		{
			static_assert(std::is_arithmetic<T>::value, "eqx::Point must have an arithmetic type");
		}

		/**
		 * @brief Initialize With Type Accurate Values From Another Point
		 * 
		 * @param other Point To Construct From
		 */
		template <typename U>
		Point(const eqx::Point<U>& other)
		{
			*this = other;
		}

		/**
		 * @brief Assign Point With Type Accurate Values From Another Point
		 * 
		 * @param other Point To Assign From
		 */
		template<typename U>
		void operator= (const Point<U>& other)
		{
			this->x = static_cast<T>(other.x);
			this->y = static_cast<T>(other.y);
			if (std::numeric_limits<U>::max() > std::numeric_limits<T>::max())
			{
				eqx::Log::log(eqx::Log::Level::warning, "Lossy Conversion", eqx::Log::Type::runtimeWarning);
			}
		}

		/**
		 * @brief This.x + Other.x, This.y + Other.y
		 * 
		 * @param other The Same Type Point We Add From
		 * 
		 * @returns Resulting Point
		 */
		Point<T> operator+ (const Point<T>& other) const
		{
			if (eqx::willOverflowAddition(this->x, other.y) ||
				eqx::willOverflowAddition(this->y, other.y))
			{
				eqx::Log::log(eqx::Log::Level::error, "Arithmetic Overflow", eqx::Log::Type::overflowError);
				return Point<T>();
			}
			else
			{
				return Point<T>(this->x + other.x, this->y + other.y);
			}
		}

		/**
		 * @brief This.x - Other.x, This.y - Other.y
		 * 
		 * @param other The Same Type Point We Subtract From
		 * 
		 * @returns Resulting Point
		 */
		Point<T> operator- (const Point<T>& other) const
		{
			if (eqx::willOverflowAddition(this->x, -other.y) ||
				eqx::willOverflowAddition(this->y, -other.y))
			{
				eqx::Log::log(eqx::Log::Level::error, "Arithmetic Overflow", eqx::Log::Type::overflowError);
				return Point<T>();
			}
			else
			{
				return Point<T>(this->x - other.x, this->y - other.y);
			}
		}

		/**
		 * @brief This.x += Other.x, This.y += Other.y
		 * 
		 * @param other The Same Type Point We Add From
		 */
		void operator+= (const Point<T>& other)
		{
			*this = *this + other;
		}

		/**
		 * @brief This.x -= Other.x, This.y -= Other.y
		 *
		 * @param other The Same Type Point We Subtract From
		 */
		void operator-= (const Point<T>& other)
		{
			*this = *this - other;
		}

		/**
		 * @brief This.x == Other.x, This.y == Other.y UNLESS FLOATING POINT
		 * @brief If Floating Point, Difference Must Be Less Than 0.001
		 * 
		 * @param other The Same Type Point We Compare Against
		 * 
		 * @returns True If Points Are Equivalent
		 */
		bool operator== (const Point<T>& other) const
		{
			return equals(*this, other);
		}

		/**
		 * @brief This.x != Other.x, This.y != Other.y UNLESS FLOATING POINT
		 * @brief If Floating Point, Difference Must Be Greater Than Or Equal To 0.001
		 *
		 * @param other The Same Type Point We Compare Against
		 *
		 * @returns True If Points Are Not Equivalent
		 */
		bool operator!= (const Point<T>& other) const
		{
			return !(*this == other);
		}

		/**
		 * @brief Creates Printable String Of Form "(x, y)"
		 * 
		 * @returns "({this->x}, {this->y})"
		 */
		std::string toString() const
		{
			std::string res = "";
			res +=
				"(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
			return res;
		}

		T x, y;
	};

	/**
	 * @brief point1.x == point2.x, point1.y == point2.y UNLESS FLOATING POINT
	 * @brief If Floating Point, Difference Must Be Less Than error
	 *
	 * @param point1 First Point
	 * @param point2 Second Point
	 * @param error Amount Of Inaccuracy Permissible For Floating Point Types
	 *
	 * @returns True If Points Are Equivalent
	 */
	template <typename T>
	bool equals(const Point<T>& point1, const Point<T>& point2, double error = 0.001)
	{
		if (std::is_integral<T>::value)
		{
			return (point1.x == point2.x) && (point1.y == point2.y);
		}
		else if (std::is_floating_point<T>::value)
		{
			return
				std::fabs(point1.x - point2.x) < static_cast<T>(error) &&
				std::fabs(point1.y - point2.y) < static_cast<T>(error);
		}
		else
		{
			eqx::Log::log(eqx::Log::Level::error, "This case should never be reached", eqx::Log::Type::unreachableCodeError);
			return false;
		}
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
	T distance(const Point<T>& point1, const Point<T>& point2)
	{
		errno = 0;
		double 
			dx = static_cast<double>(eqx::distance(point1.x, point2.x)),
			dy = static_cast<double>(eqx::distance(point1.y, point2.y)),
			result = std::hypot(dx, dy);
		if (errno == ERANGE ||
			result > std::numeric_limits<T>::max() ||
			result < std::numeric_limits<T>::lowest())
		{
			eqx::Log::log(eqx::Log::Level::error, "Arithmetic Overflow", eqx::Log::Type::overflowError);
			return static_cast<T>(0);
		}
		else
		{
			return static_cast<T>(result);
		}
	}

	/**
	 * @brief Normalize A Point As If It Were A Vector From The Origin (0, 0)
	 * 
	 * @param point Point To Be Normalized
	 * 
	 * @returns Normalized Point
	 */
	template <typename T>
	Point<T> normalize(const Point<T>& point)
	{
		if (std::is_integral<T>::value)
		{
			eqx::Log::log(eqx::Log::Level::warning, "Normalizing integral value!", eqx::Log::Type::runtimeWarning);
		}
		
		Point<T> origin = { static_cast<T>(0), static_cast<T>(0) }, result;
		result.x = eqx::distance(origin, point) == static_cast<T>(0) ? static_cast<T>(0) : point.x / distance(origin, point);
		result.y = eqx::distance(origin, point) == static_cast<T>(0) ? static_cast<T>(0) : point.y / distance(origin, point);
		return result;
	}

	/**
	 * @brief Compute The Angle Of A Point In Degrees From The Origin (0, 0)
	 * 
	 * @param point Point The Angle Is Computed From
	 * 
	 * @returns Angle In Degrees
	 */
	template <typename T>
	double angle(const Point<T>& point)
	{
		Point<T> normPoint = eqx::normalize(point);
		std::pair<double, double> 
			sinVals = eqx::arcsin(normPoint.y),
			cosVals = eqx::arccos(normPoint.x);

		return
			(eqx::equals(sinVals.first, cosVals.first) ||
			eqx::equals(sinVals.first, cosVals.second)) ?
			sinVals.first : sinVals.second;
	}
}