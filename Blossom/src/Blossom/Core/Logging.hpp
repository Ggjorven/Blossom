#pragma once

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Blossom
{

	class Log
	{
	public:
		enum class Level
		{
			None = -1, Trace, Info, Warn, Error, Fatal
		};

		static void Init();

		template<typename ... Args>
		static void LogMessage(Log::Level level, Args&&... args);

		#define BL_LOG_TRACE(...)	Blossom::Log::LogMessage(Blossom::Log::Level::Trace, __VA_ARGS__);
		#define BL_LOG_INFO(...)	Blossom::Log::LogMessage(Blossom::Log::Level::Info, __VA_ARGS__);
		#define BL_LOG_WARN(...)	Blossom::Log::LogMessage(Blossom::Log::Level::Warn, __VA_ARGS__);
		#define BL_LOG_ERROR(...)	Blossom::Log::LogMessage(Blossom::Log::Level::Error, __VA_ARGS__);
		#define BL_LOG_FATAL(...)	Blossom::Log::LogMessage(Blossom::Log::Level::Fatal, __VA_ARGS__);

	private:
		static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> s_Sink;
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

	template<typename ... Args>
	void Log::LogMessage(Log::Level level, Args&&... args)
	{
		switch (level)
		{
		case Level::Trace:
			spdlog::trace(fmt::format(std::forward<Args>(args)...));
			break;
		case Level::Info:
			spdlog::info(fmt::format(std::forward<Args>(args)...));
			break;
		case Level::Warn:
			spdlog::warn(fmt::format(std::forward<Args>(args)...));
			break;
		case Level::Error:
			spdlog::error(fmt::format(std::forward<Args>(args)...));
			break;
		case Level::Fatal:
			spdlog::critical(fmt::format(std::forward<Args>(args)...));
			break;
		}
	}

}