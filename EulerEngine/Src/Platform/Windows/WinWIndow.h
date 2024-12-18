#pragma once
#include "../../Core/EulerWindow.h"
#include "GLFW/glfw3.h"
namespace EulerEngine {
	class WinWindow :public EulerWindow {
	public:
		WinWindow(const WindowInfo& info);
		virtual ~WinWindow();

		void OnUpdate() override;

		inline int GetWidth() const override { return m_Data.Width; }
		inline int GetHeight() const override { return m_Data.Height; }
		inline void SetEventCallback(const EventCallbackFunc& callback) override { m_Data.Callback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		virtual void Initialize(const WindowInfo& info);
		virtual void ShutDown();
	private:
		GLFWwindow* m_Window;
		struct WindowData{
			std::string Title;
			int Width;
			int Height;
			bool VSync;
			EventCallbackFunc Callback;
		}m_Data;
	};
}