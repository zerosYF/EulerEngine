#pragma once
#include"../gkpch.h"
#include"../GutKink/Core.h"
#include"Events/Event.h"
namespace EulerEngine {
	struct WindowInfo
	{
		int Width;
		int Height;
		std::string Title;
		WindowInfo(const std::string& title = "Euler Engine", int width = 1280, int height = 768)
			:Title(title), Width(width), Height(height) {
		}
	};


	class KINK_API EulerWindow 
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;
		virtual ~EulerWindow() {}
		virtual void OnUpdate() = 0;
		virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;
		
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;

		static EulerWindow* Create(const WindowInfo& info = WindowInfo());
	};
}