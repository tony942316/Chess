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

#include <functional>
#include <chrono>

#include "eqx_StopWatch.hpp"

namespace eqx
{
	class Benchmark
	{
	public:
		/**
		 * @brief Construct Benchmark With A Function To Test
		 * 
		 * @param function The Function To Be Tested
		 */
		explicit Benchmark(std::function<void(void)> function) noexcept
			:
			m_Function(function),
			m_Bench(std::chrono::nanoseconds())
		{
		}

		/**
		 * Trivial Move And Copy Operation
		 */
		Benchmark(const Benchmark&) = default;
		Benchmark(Benchmark&&) = default;
		Benchmark& operator= (const Benchmark&) = default;
		Benchmark& operator= (Benchmark&&) = default;
		~Benchmark() = default;

		/**
		 * @brief Time How Long It Takes To Run The Function
		 */
		void bench() noexcept(noexcept(m_Function()))
		{
			StopWatch timer;
			timer.start();
			m_Function();
			timer.stop();
			m_Bench = timer.getDuration<std::chrono::nanoseconds>();
		}

		/**
		 * @brief Time How Long It Takes To Run The Function On Average
		 * 
		 * @param runs The Number Of Times The Function Is Run
		 */
		void avgBench(int runs = 1'000) noexcept(noexcept(m_Function()))
		{
			StopWatch timer;
			timer.start();
			for (int i = 0; i < runs; i++)
			{
				bench();
			}
			timer.stop();
			m_Bench = static_cast<std::chrono::nanoseconds>(
				timer.getTime<std::chrono::nanoseconds>() / runs);
		}

		/**
		 * @brief Build A String Representing The Time It Took To Run
		 *		The Function
		 * 
		 * @returns std::string Of Form "Bench: X TimeUnits"
		 */
		template <eqx::timeUnit T = std::chrono::milliseconds>
		[[nodiscard]] std::string toString() const
		{
			auto result = std::string("");
			result += "Bench: "; 
			result += 
				std::to_string(std::chrono::duration_cast<T>(m_Bench).count());
			if constexpr (std::same_as<T, std::chrono::nanoseconds>)
			{
				result += " ns";
			}
			else if constexpr (std::same_as<T, std::chrono::microseconds>)
			{
				result += " us";
			}
			else if constexpr (std::same_as<T, std::chrono::milliseconds>)
			{
				result += " ms";
			}
			else if constexpr (std::same_as<T, std::chrono::seconds>)
			{
				result += " s";
			}
			return result;
		}

	private:
		std::function<void(void)> m_Function;
		std::chrono::nanoseconds m_Bench;
	};
}