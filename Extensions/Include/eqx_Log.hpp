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

#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <source_location>

#include <array>

#include "eqx_SuperEnum.hpp"

namespace eqx
{
	/**
	 * @brief Logs Errors And Warnings To A Stream And A File
	 */
	class Log
	{
	public:
		/**
		 * Pure Static Class Is Not Ment To Be Constructed Or Copied
		 */
		Log() = delete;
		Log(const Log&) = delete;
		Log(Log&&) = delete;
		Log& operator= (const Log&) = delete;
		Log& operator= (Log&&) = delete;
		~Log() = delete;

		/**
		 * @brief Severity Of A Log
		 */
		EQX_SUPER_ENUM(Level, 
			all, 
			info, 
			warning, 
			error, 
			none
		)

		/**
		 * @brief Type Of A Log
		 */
		EQX_SUPER_ENUM(Type,
			none,
			info,
			runtimeWarning,
			runtimeError,
			overflowError,
			unreachableCodeError
		)

		/**
		 * @brief Log A Message To The Active Stream And File
		 * 
		 * @param level Level Of The Log
		 * @param msg Message Of The Log
		 * @param type Type Of The Log
		 * @param loc Current Location In Source
		 */
		static void log(Level level, std::string_view msg, 
			Type type = Type::none, 
			const std::source_location& loc = std::source_location::current());

		/**
		 * @brief Set Level Of Logs To Be Output i.e.
		 * warning Will Output warnings And errors But Not info
		 * 
		 * @param level Cutoff i.e. all -> info -> warning -> error -> none
		 */
		static void setLevel(Level level) noexcept;

		/**
		 * @brief Set The Stream Logs Are Written To
		 * 
		 * @param stream The New Output Stream
		*/
		static void setOutputStream(std::ostream& stream) noexcept;

		/**
		 * @brief Set The File Logs Are Written To
		 * 
		 * @param file The Path Of The New File
		 */
		static void setOutputFile(std::string_view file);

		/**
		 * @brief Clears The Last Error Message And Type
		 */
		static void clear() noexcept;

		/**
		 * @brief Get Current Log Level
		 * 
		 * @returns Current Log Level
		 */
		static Level getCurrentLogLevel() noexcept;

		/**
		 * @brief Get Type Of Last Log
		 * 
		 * @returns Last Log Type
		 */
		static Type getLastLogType() noexcept;

		/**
		 * @brief Get Message Of Last Log
		 * 
		 * @returns Last Message String
		 */
		static std::string_view getLastLogMessage() noexcept;

		/**
		 * @brief Build String With eqx::Log Formatting i.e.
		 *		"{SourceLocation}[{Log::Level}]: {Message}"
		 * 
		 * @param loc Location Of The Log
		 * @param level Level Of The Log
		 * @param msg Message Of The Log
		 * 
		 * @returns Formatted String
		 */
		static std::string getFormattedString(
			const std::source_location& loc, Level level,
			std::string_view msg = "");

		/**
		 * @brief Get Log Levels That Log Properly i.e.
		 *		eqx::Log::all Is Not Meant To Be Logged
		 * 
		 * @returns std::vector Of Loggable Levels
		 */
		static inline consteval std::array<eqx::Log::Level, 3ULL> 
			getLoggableLevels()
		{
			return { eqx::Log::Level::info,
				eqx::Log::Level::warning,
				eqx::Log::Level::error };
		}

	private:
		static std::ofstream s_LogFile;
		static std::ostream* s_OutputStream;
		static Level s_LogLevel;
		static Type s_LastErrorType;
		static std::string s_LastMessage;
	};
}