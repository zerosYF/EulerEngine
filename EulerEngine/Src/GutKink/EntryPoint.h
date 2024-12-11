#pragma once
#ifdef KINK_PLATFORM_WINDOWS
extern EulerEngine::Application* EulerEngine::CreateApplication();
int main(int argc, char** argv) {
	printf("welcome euler's world!\n");

	EulerEngine::EulerLog::Init();
	EulerEngine::EulerLog::GetCoreLogger()->warn("this is a warning!");
	EulerEngine::EulerLog::GetClientLogger()->info("this is information!");

	auto app = EulerEngine::CreateApplication();
	app->Run();
	delete app;
}
#else
#error this engine only support windows
#endif