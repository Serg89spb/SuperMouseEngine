#pragma once

#include "spdlog/spdlog.h"

namespace super_mouse
{

	class Log
	{
	public:
		static void init();

		static std::shared_ptr<spdlog::logger>& get_logger() { return _sLogger; }

	private:
		static std::shared_ptr<spdlog::logger> _sLogger;
	};

}  // namespace super_mouse

#define TETRIS_TRACE(...) ::super_mouse::Log::get_logger()->trace(__VA_ARGS__)
#define TETRIS_INFO(...) ::super_mouse::Log::get_logger()->info(__VA_ARGS__)
#define TETRIS_WARN(...) ::super_mouse::Log::get_logger()->warn(__VA_ARGS__)
#define TETRIS_ERROR(...) ::super_mouse::Log::get_logger()->error(__VA_ARGS__)
