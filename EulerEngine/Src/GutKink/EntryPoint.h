#pragma once
#ifdef KINK_PLATFORM_WINDOWS
extern EulerEngine::Application* EulerEngine::CreateApplication();
int main(int argc, char** argv) {

	EulerEngine::EulerLog::Init();
	KINK_CORE_WARN("this is a warning!");
	KINK_INFO("this is information!");

	auto app = EulerEngine::CreateApplication();
	app->Run();
	delete app;
}
#else
#error this engine only support windows
#endif