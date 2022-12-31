#pragma once

#include <string>

#include "Point.h"
#include "Mathematics.h"

namespace eqx
{
	/**
	 * @brief Rectangle On The Cartesian Plane
	 * @brief Must Be Arithmetic Type
	 */
	template<class T>
	class Rectangle
	{
	public:
		/**
		 * @brief Initialized With A Type Accurate Zero
		 */
		Rectangle()
			:
			Rectangle(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0))
		{
		}

		/**
		 * @brief Initalize With Values
		 * 
		 * @param x The x Value
		 * @param y The y Value
		 * @param w The Width
		 * @param h The Height
		 */
		Rectangle(T x, T y, T w, T h)
			:
			x(x),
			y(y),
			w(w),
			h(h)
		{
			static_assert(std::is_arithmetic<T>::value, "eqx::Rectangle must have an arithmetic type");
		}

		/**
		 * @brief Initialize With Type Accurate Values From Another Rectangle
		 * 
		 * @param other Rectangle To Construct From
		 */
		template<typename U>
		Rectangle(const eqx::Rectangle<U>& other)
		{
			*this = other;
		}

		/**
		 * @brief Assign Rectangle With Type Accurate Values From Another Rectangle
		 * 
		 * @param other Rectangle To Assign From
		 */
		template<typename U>
		void operator= (const Rectangle<U>& other)
		{
			this->x = static_cast<T>(other.x);
			this->y = static_cast<T>(other.y);
			this->w = static_cast<T>(other.w);
			this->h = static_cast<T>(other.h);
			if (std::numeric_limits<U>::max() > std::numeric_limits<T>::max())
			{
				eqx::Log::log(eqx::Log::Level::warning, "Lossy Conversion", eqx::Log::Type::runtimeWarning);
			}
		}

		/**
		 * @brief Create A Point At (X, Y)
		 * @brief Alias For GetTopLeftPoint
		 * 
		 * @returns eqx::Point Of Same Type
		 */
		eqx::Point<T> getLocation() const
		{
			return getTopLeftPoint();
		}

		/**
		 * @brief Create A Point At (X, Y)
		 * 
		 * @returns eqx::Point Of Same Type
		 */
		eqx::Point<T> getTopLeftPoint() const
		{
			return eqx::Point<T>(x, y);
		}

		/**
		 * @brief Create A Point At (X + W, Y)
		 * 
		 * @returns eqx::Point Of Same Type
		 */
		eqx::Point<T> getTopRightPoint() const
		{
			if (eqx::willOverflowAddition(x, w))
			{
				eqx::Log::log(eqx::Log::Level::error, "Arithmetic Overflow", eqx::Log::Type::overflowError);
				return eqx::Point<T>();
			}
			else
			{
				return eqx::Point<T>(x + w, y);
			}
		}

		/**
		 * @brief Create A Point At (X, Y + H)
		 * 
		 * @returns eqx::Point Of Same Type
		 */
		eqx::Point<T> getBottomLeftPoint() const
		{
			if (eqx::willOverflowAddition(y, h))
			{
				eqx::Log::log(eqx::Log::Level::error, "Arithmetic Overflow", eqx::Log::Type::overflowError);
				return eqx::Point<T>();
			}
			else
			{
				return eqx::Point<T>(x, y + h);
			}
		}

		/**
		 * @brief Create A Point At (X + W, Y + H)
		 * 
		 * @returns eqx::Point Of Same Type
		 */
		eqx::Point<T> getBottomRightPoint() const
		{
			if (eqx::willOverflowAddition(x, w) ||
				eqx::willOverflowAddition(y, h))
			{
				eqx::Log::log(eqx::Log::Level::error, "Arithmetic Overflow", eqx::Log::Type::overflowError);
				return eqx::Point<T>();
			}
			else
			{
				return eqx::Point<T>(x + w, y + h);
			}
		}

		/**
		 * @brief Create A Point At (X + 0.5 * W, Y + 0.5 * H)
		 * 
		 * @returns eqx::Point Of Same Type
		 */
		eqx::Point<T> getCenterPoint() const
		{
			T dx = static_cast<T>(w / static_cast<T>(2));
			T dy = static_cast<T>(h / static_cast<T>(2));
			if (eqx::willOverflowAddition(x, dx) ||
				eqx::willOverflowAddition(y, dy))
			{
				eqx::Log::log(eqx::Log::Level::error, "Arithmetic Overflow", eqx::Log::Type::overflowError);
				return eqx::Point<T>();
			}
			else
			{
				return eqx::Point<T>(x + dx, y + dy);
			}
		}

		/**
		 * @brief Creates Printable String Of Form "(x, y, w, h)"
		 * 
		 * @returns "({this->x}, {this->y}, {this->w}, {this->h})"
		 */
		std::string toString() const
		{
			std::string res = "";
			res +=
				"(" + std::to_string(x) + ", " + std::to_string(y) +
				", " + std::to_string(w) + ", " + std::to_string(h) + ")";
			return res;
		}

		T x, y, w, h;
	};

	/**
	 * @brief Determine If A Point Is Contained Inside A Rectangle
	 * 
	 * @param rect The Rectangle
	 * @param point The Point
	 * 
	 * @returns True If point Is Contained By rect
	 */
	template <typename U>
	bool intersect(const Rectangle<U>& rect, const Point<U>& point)
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
	 * @returns True If There Is Any Overlap Between The Two Rectangles
	 */
	template <typename U>
	bool intersect(const Rectangle<U>& rect1, const Rectangle<U>& rect2)
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