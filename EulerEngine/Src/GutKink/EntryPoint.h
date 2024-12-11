#pragma once
#ifdef KINK_PLATFORM_WINDOWS
extern EulerEngine::Application* EulerEngine::CreateApplication();
int main(int argc, char** argv) {
	printf("welcome euler engine!\n");
	auto app = EulerEngine::CreateApplication();
	app->Run();
	delete app;
}
#else
#error this engine only support windows
#endif