#pragma once

#include <chrono>

namespace eqx
{
	class StopWatch
	{
	public:
		/**
		 * @brief Starts StopWatch On Construction
		 */
		StopWatch();

		/**
		 * @brief Set The Start Time Of The StopWatch And Reset The End Time
		 */
		void start();

		/**
		 * @brief Set The End Time Of The StopWatch
		 */
		void stop();

		/**
		 * @brief Stops And Gives Past Time In Seconds
		 * 
		 * @returns Past Time In Seconds
		 */
		long long readTimeSeconds();

		/**
		 * @brief Stops And Gives Past Time In MilliSeconds
		 *
		 * @returns Past Time In MilliSeconds
		 */
		long long readTimeMilli();

		/**
		 * @brief Stops And Gives Past Time In MicroSeconds
		 *
		 * @returns Past Time In MicroSeconds
		 */
		long long readTimeMicro();

		/**
		 * @brief Stops And Gives Past Time In NanoSeconds
		 *
		 * @returns Past Time In NanoSeconds
		 */
		long long readTimeNano();

		/**
		 * @brief Gives Past Time From Last Stop In Seconds
		 * 
		 * @returns Past Time In Seconds
		 */
		long long getTimeSeconds() const;

		/**
		 * @brief Gives Past Time From Last Stop In MilliSeconds
		 *
		 * @returns Past Time In MilliSeconds
		 */
		long long getTimeMilli() const;

		/**
		 * @brief Gives Past Time From Last Stop In MicroSeconds
		 *
		 * @returns Past Time In MicroSeconds
		 */
		long long getTimeMicro() const;

		/**
		 * @brief Gives Past Time In NanoSeconds
		 *
		 * @returns Past Time In NanoSeconds
		 */
		long long getTimeNano() const;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime, m_EndTime;
	};
}