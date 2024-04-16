#include <memory>
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace super_mouse
{
	std::shared_ptr<spdlog::logger> Log::_sLogger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		_sLogger = spdlog::stdout_color_mt("SME");
		_sLogger->set_level(spdlog::level::trace);
	}
}  // namespace super_mouse