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

#include <chrono>

namespace eqx
{
	namespace shortTimeUnits
	{
		using tu_ns = std::chrono::nanoseconds;
		using tu_us = std::chrono::microseconds;
		using tu_ms = std::chrono::milliseconds;
		using tu_s = std::chrono::seconds;
	}

	template <typename T>
	concept timeUnit =
		std::is_same_v<T, std::chrono::nanoseconds> ||
		std::is_same_v<T, std::chrono::microseconds> ||
		std::is_same_v<T, std::chrono::milliseconds> ||
		std::is_same_v<T, std::chrono::seconds>;

	class StopWatch
	{
	public:
		/**
		 * @brief Starts StopWatch On Construction
		 */
		explicit StopWatch() noexcept
		{
			start();
		}

		/**
		 * Trivial Move And Copy Operation
		 */
		StopWatch(const StopWatch& other) = default;
		StopWatch(StopWatch&& other) = default;
		StopWatch& operator= (const StopWatch& other) = default;
		StopWatch& operator= (StopWatch&& other) = default;
		~StopWatch() = default;

		/**
		 * @brief Set The Start Time Of The StopWatch And Reset The End Time
		 */
		void start() noexcept
		{
			m_StartTime = std::chrono::steady_clock::now();
			m_EndTime = m_StartTime;
		}

		/**
		 * @brief Set The End Time Of The StopWatch
		 */
		void stop() noexcept
		{
			m_EndTime = std::chrono::steady_clock::now();
		}

		/**
		 * @brief Gives The std::chrono::duration<T> Between The Last
		 *		this->start Call And this->stop
		 *
		 * @returns std::chrono::duration<T> Between The Last this->start() 
		 *		Call And this->stop Call
		 */
		template <timeUnit T = std::chrono::milliseconds>
		[[nodiscard]] T getDuration() const noexcept
		{
			return std::chrono::duration_cast<T>(m_EndTime - m_StartTime);
		}

		/**
		 * @brief Gives The Time Between The Last this->start Call And
		 *		this->stop Call In Milliseconds (Or T If Defined)
		 *
		 * @returns long long Representing The Milliseconds (Or T) Past Between
		 *		The Last this->start Call And this->stop Call
		 */
		template <timeUnit T = std::chrono::milliseconds>
		[[nodiscard]] long long getTime() const noexcept
		{
			return getDuration<T>().count();
		}

		/**
		 * @brief Gives The Time Between The Last this->start Call And
		 *		The Current Time In Milliseconds (Or T If Defined), Note That
		 *		this->stop Is Called
		 *
		 * @returns long long Representing The Milliseconds (Or T) Past Between
		 *		The Last this->start Call The Current Time
		 */
		template <timeUnit T = std::chrono::milliseconds>
		[[nodiscard]] long long readTime() noexcept
		{
			stop();
			return getTime<T>();
		}

	private:
		std::chrono::time_point<std::chrono::steady_clock> m_StartTime, 
			m_EndTime;
	};
}