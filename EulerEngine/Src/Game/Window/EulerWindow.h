#pragma once
#include<functional>
#include<vector>
namespace EulerEngine {
	struct  WindowInfo
	{
		float width = 1280.0f;
		float height = 900.0f;
		const char* title{"EulerEngine"};
		bool isFullScreen = false;
	};
	class WindowSystem {
	public:
		WindowSystem() = default;
		~WindowSystem();
		void Initialize(WindowInfo);
		void PollEvents() const;
		bool ShouldClose() const;
		float getWIndowWidth() const;
		float getWindowHeight() const;
	};
}