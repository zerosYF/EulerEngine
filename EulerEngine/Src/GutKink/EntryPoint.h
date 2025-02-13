#pragma once
#ifdef KINK_PLATFORM_WINDOWS
extern EulerEngine::Application* EulerEngine::CreateApplication();
void main(int argc, char** argv) {

	EulerEngine::EulerLog::Init();
	KINK_CORE_INFO("Welcome to Euler's World!");
	KINK_PROFILE_BEGIN_SESSION("Startup", "EulerEngineProfile_Startup.json");
	auto app = EulerEngine::CreateApplication();
	KINK_PROFILE_END_SESSION();

	KINK_PROFILE_BEGIN_SESSION("Runtime", "EulerEngineProfile_Runtime.json");
	app->Run();
	KINK_PROFILE_END_SESSION();

	KINK_PROFILE_BEGIN_SESSION("Shutdown", "EulerEngineProfile_Shutdown.json");
	delete app;
	KINK_PROFILE_END_SESSION();
}
#else
#error this engine only support windows
#endif