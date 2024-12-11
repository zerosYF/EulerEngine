#include "EulerLog.h"
namespace EulerEngine {

	std::shared_ptr<spdlog::logger> EulerLog::s_CoreLogger;
	std::shared_ptr<spdlog::logger> EulerLog::s_ClientLogger;
	
	void EulerLog::Init()
	{
		printf("--------------------------log init-----------------------------");
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("Euler");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}
