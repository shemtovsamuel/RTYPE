#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cstdarg>

namespace factorio {
	namespace debug {
		/**
		 * @brief Logger class, used to log messages in the console.
		 * 
		 */
		class Logger
		{
		public:
			/**
			 * @brief Get the instance object
			 * 
			 * @return Logger& The instance of the logger
			 */
			static Logger& getInstance()
			{
				static Logger instance;
				return instance;
			}

			/**
			 * @brief Log a message with an extern file
			 * 
			 * @tparam Args 
			 * @param message 
			 * @param args 
			 */
			template<typename... Args>
			void Trace(const char* message, Args... args)
			{
				int size = snprintf(nullptr, 0, message, args...) + 1;
				std::unique_ptr<char[]> buf(new char[size]);
				snprintf(buf.get(), size, message, args...);
				std::ostringstream string_stream;
				string_stream << "[Trace]\t";
				string_stream << buf.get();
				string_stream << "\n";
				logs.push_back(string_stream.str());
			}

			/**
			 * @brief Log a message with Debug informations
			 * 
			 * @tparam Args 
			 * @param message 
			 * @param args 
			 */
			template<typename... Args>
			void Debug(const char* message, Args... args)
			{
				int size = snprintf(nullptr, 0, message, args...) + 1;
				std::unique_ptr<char[]> buf(new char[size]);
				snprintf(buf.get(), size, message, args...);
				std::ostringstream string_stream;
				string_stream << "[Debug]\t";
				string_stream << buf.get();
				string_stream << "\n";
				logs.push_back(string_stream.str());
			}

			/**
			 * @brief Log a message with informations
			 * 
			 * @tparam Args 
			 * @param message 
			 * @param args 
			 */
			template<typename... Args>
			void Info(const char* message, Args... args)
			{
				int size = snprintf(nullptr, 0, message, args...) + 1;
				std::unique_ptr<char[]> buf(new char[size]);
				snprintf(buf.get(), size, message, args...);
				std::ostringstream string_stream;
				string_stream << "[Info]\t";
				string_stream << buf.get();
				string_stream << "\n";
				logs.push_back(string_stream.str());
			}

			/**
			 * @brief Log a message with a warning
			 * 
			 * @tparam Args 
			 * @param message 
			 * @param args 
			 */
			template<typename... Args>
			void Warning(const char* message, Args... args)
			{
				int size = snprintf(nullptr, 0, message, args...) + 1;
				std::unique_ptr<char[]> buf(new char[size]);
				snprintf(buf.get(), size, message, args...);
				std::ostringstream string_stream;
				string_stream << "[Warning]\t";
				string_stream << buf.get();
				string_stream << "\n";
				logs.push_back(string_stream.str());
			}

			/**
			 * @brief Log a message with an error
			 * 
			 * @tparam Args 
			 * @param message 
			 * @param args 
			 */
			template<typename... Args>
			void Error(const char* message, Args... args)
			{
				int size = snprintf(nullptr, 0, message, args...) + 1;
				std::unique_ptr<char[]> buf(new char[size]);
				snprintf(buf.get(), size, message, args...);
				std::ostringstream string_stream;
				string_stream << "[Error]\t";
				string_stream << buf.get();
				string_stream << "\n";
				logs.push_back(string_stream.str());
			}

			/**
			 * @brief Log a message with a critical error
			 * 
			 * @tparam Args 
			 * @param message 
			 * @param args 
			 */
			template<typename... Args>
			void Critical(const char* message, Args... args)
			{
				int size = snprintf(nullptr, 0, message, args...) + 1;
				std::unique_ptr<char[]> buf(new char[size]);
				snprintf(buf.get(), size, message, args...);
				std::ostringstream string_stream;
				string_stream << "[Critical]\t";
				string_stream << buf.get();
				string_stream << "\n";
				logs.push_back(string_stream.str());
			}

			/**
			 * @brief Draw the log window
			 * 
			 */
			void DrawLogWindow();

		private:
			Logger() {}
			Logger(const Logger&) = delete;
			Logger& operator=(const Logger&) = delete;

			std::vector<std::string> logs;
		};
	}
}