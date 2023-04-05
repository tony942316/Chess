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

#include <random>
#include <type_traits>
#include <concepts>

#include "eqx_Misc.hpp"
#include "eqx_Mathematics.hpp"

namespace eqx::Random
{
	/**
	 * @brief Random Engine Used With eqx::Random Functions
	 */
	extern std::mt19937_64 p_engine;

	/**
	 * @brief Simulate A Coin Flip
	 *
	 * @returns Either 1 Or 0
	 */
	unsigned int flipCoin();

	/**
	 * @brief Generate A Random Integral Type Number
	 * 
	 * @param lowerBound Lowest Possible Value
	 * @param upperBound Highest Possible Value
	 * 
	 * @returns Random Integral Type Number
	 *		In Range [lowerBound, upperBound]
	 */
	template <std::integral T>
	T randomNumber(T lowerBound, T upperBound)
	{
		static auto dist =
			std::uniform_int_distribution<T>(lowerBound, upperBound);

		eqx::runtimeAssert(lowerBound < upperBound,
			"Lower Bound Is Larger Than UpperBound!");

		if (lowerBound != dist.min() || upperBound != dist.max())
		{
			dist = 
				std::uniform_int_distribution<T>(lowerBound, upperBound);
		}

		return dist(p_engine);
	}

	/**
	 * @brief Generate A Random Floating Point Type Number
	 * @brief Note That For Ranges Where lowerBound Is Negative And upperBound
	 *		Positive There Is A Bias For The Generation Of (T)0.0, The P(0) Is 
	 *		Exactly 2/N Where N Is The Number Of Possible Generated Values.
	 *		The Bias Is Sufficiently Small For The Typical Cases, However In
	 *		The Case of [-e, e] Where e = std::numeric_limits<T>::denorm_min()
	 *		(T)0.0 Has A 50% Probablility Of Generation. For Cases As Such It
	 *		Is Recommended To Use Integral Types.
	 *
	 * @param lowerBound Lowest Possible Value
	 * @param upperBound Highest Possible Value
	 *
	 * @returns Random Floating Point Type Number
	 *		In Range [lowerBound, upperBound]
	 */
	template <std::floating_point T>
	T randomNumber(T lowerBound, T upperBound)
	{
		static auto dist = std::uniform_real_distribution<T>();

		eqx::runtimeAssert(upperBound >= lowerBound,
			"Lower Bound Is Larger Than UpperBound!");

		if (lowerBound >= eqx::zero<T> && upperBound >= eqx::zero<T>)
		{
			auto prevErr = errno;
			T decoyValue = std::nexttoward(lowerBound,
				std::numeric_limits<T>::lowest());
			errno = prevErr;
			dist = std::uniform_real_distribution<T>(
				decoyValue, upperBound);
			double producedValue = dist(p_engine);
			if (producedValue == decoyValue)
			{
				return upperBound;
			}
			else
			{
				return producedValue;
			}
		}
		else if (lowerBound <= eqx::zero<T> && upperBound <= eqx::zero<T>)
		{
			return -randomNumber(-upperBound, -lowerBound);
		}
		else if (lowerBound < eqx::zero<T> && upperBound > eqx::zero<T>)
		{
			T offset = (-upperBound - lowerBound) / static_cast<T>(2.0);
			if (flipCoin())
			{
				return 
					randomNumber(lowerBound + offset, eqx::zero<T>) - offset;
			}
			else
			{
				return 
					randomNumber(eqx::zero<T>, upperBound + offset) - offset;
			}
		}
		else
		{
			eqx::runtimeAssert(false, "Code Should Never Reach This!");
			return eqx::zero<T>;
		}
	}

	/**
	 * @brief Simulate A Dice Roll
	 * 
	 * @param sides Number Of Sides On The Dice
	 * 
	 * @returns An Unsigned Int In Range [1, sides]
	 */
	unsigned int rollDice(unsigned int sides = 6U);

	/**
	 * @brief Generate A Random Seed
	 * 
	 * @returns Seed
	 */
	unsigned int generateSeed();
}