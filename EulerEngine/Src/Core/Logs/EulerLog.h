#pragma once
#include"../../GutKink/Core.h"
#include"spdlog/spdlog.h"
#include"spdlog/sinks/stdout_color_sinks.h"
#include"spdlog/fmt/ostr.h"
namespace EulerEngine {
	class KINK_API EulerLog {
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}
#define KINK_CORE_ERROR(...)	EulerEngine::EulerLog::GetCoreLogger()->error(__VA_ARGS__)
#define KINK_CORE_WARN(...)		EulerEngine::EulerLog::GetCoreLogger()->warn(__VA_ARGS__)
#define KINK_CORE_INFO(...)		EulerEngine::EulerLog::GetCoreLogger()->info(__VA_ARGS__)
#define KINK_CORE_TRACE(...)	EulerEngine::EulerLog::GetCoreLogger()->trace(__VA_ARGS__)
#define KINK_CORE_FATAL(...)	EulerEngine::EulerLog::GetCoreLogger()->info(__VA_ARGS__)


#define KINK_ERROR(...)		EulerEngine::EulerLog::GetClientLogger()->error(__VA_ARGS__)
#define KINK_WARN(...)		EulerEngine::EulerLog::GetClientLogger()->warn(__VA_ARGS__)
#define KINK_INFO(...)		EulerEngine::EulerLog::GetClientLogger()->info(__VA_ARGS__)
#define KINK_TRACE(...)		EulerEngine::EulerLog::GetClientLogger()->trace(__VA_ARGS__)
#define KINK_FATAL(...)		EulerEngine::EulerLog::GetClientLogger()->info(__VA_ARGS__)



