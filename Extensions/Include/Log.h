#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <source_location>

namespace eqx
{
	/**
	 * @brief Logs Errors And Warnings To A Stream And A File
	 */
	class Log
	{
	public:
		Log(const Log& l) = delete;
		void operator= (const Log& l) = delete;

		/**
		 * @brief Severity Of A Log
		 */
		enum class Level
		{
			info,
			warning,
			error,
			none
		};

		/**
		 * @brief Type Of A Log
		 */
		enum class Type
		{
			none,
			info,
			runtimeWarning,
			runtimeError,
			overflowError,
			unreachableCodeError
		};

		/**
		 * @brief Log A Message To The Active Stream And File
		 * 
		 * @param level Level Of The Log
		 * @param msg Message Of The Log
		 * @param type Type Of The Log
		 * @param loc Current Location In Source
		 */
		static void log(Level level, const std::string& msg, Type type = Type::none, const std::source_location& loc = std::source_location::current());

		/**
		 * @brief Set Level Of Logs To Be Output
		 * 
		 * @param level Cutoff
		 */
		static void setLevel(Level level);

		/**
		 * @brief Set The Stream Logs Are Written To
		 * 
		 * @param stream The New Output Stream
		*/
		static void setOutputStream(const std::ostream& stream);

		/**
		 * @brief Set The File Logs Are Written To
		 * 
		 * @param file The New File
		 */
		static void setOutputFile(const std::string& file);

		/**
		 * @brief Clears The Last Error Message And Type
		 */
		static void clear();

		/**
		 * @brief Get Type Of Last Log
		 * 
		 * @returns Last Log Type
		 */
		static Type getLastLogType();

		/**
		 * @brief Get Message Of Last Log
		 * 
		 * @returns Last Message String
		 */
		static const std::string& getLastLogMessage();

	private:
		Log();

		static Log& getInstance();

		std::ofstream m_LogFile;
		std::ostream m_OutputStream;
		Level m_LogLevel;
		Type m_LastErrorType;
		std::string m_LastMessage;
	};
}