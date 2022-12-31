#pragma once

#include <random>

namespace eqx
{
	/**
	 * @brief Random Number Generator API
	 */
	class Random
	{
	public:
		Random(const Random& r) = delete;
		void operator =(const Random& r) = delete;

		/**
		 * @brief Generate A Random Integer
		 * 
		 * @param lowerBound Lowest Possible Value
		 * @param upperBound Highest Possible Value
		 * @returns Random Integer
		 */
		static int randInt(int lowerBound, int upperBound);

		/**
		 * @brief Generate A Random Unsigned Integer
		 *
		 * @param lowerBound Lowest Possible Value
		 * @param upperBound Highest Possible Value
		 * @returns Random Unsigned Integer
		 */
		static unsigned int randUnsignedInt(unsigned int lowerBound, unsigned int upperBound);

		/**
		 * @brief Generate A Random Double
		 * 
		 * @param lowerBound Lowest Possible Value
		 * @param upperBound Highest Possible Value
		 * @returns Random Double
		*/
		static double randDouble(double lowerBound, double upperBound);

		/**
		 * @brief Simulate A Coin Flip
		 * 
		 * @returns 1 For Heads 0 For Tails
		 */
		static int flipCoin();

		/**
		 * @brief Simulate A Dice Roll
		 * 
		 * @param sides Number Of Sides On The Dice
		 * @returns The Number The Dice Lands On
		 */
		static unsigned int rollDice(unsigned int sides = 6);

		/**
		 * @brief Generate A Random Seed From Current Time
		 * 
		 * @returns Seed
		*/
		static unsigned int generateSeed();

	private:
		Random();

		static Random& getInstance();

		std::mt19937_64 engine;
		std::uniform_int_distribution<int> uniInt;
		std::uniform_int_distribution<unsigned int> uniUInt;
		std::uniform_real_distribution<double> uniDouble;
	};
}