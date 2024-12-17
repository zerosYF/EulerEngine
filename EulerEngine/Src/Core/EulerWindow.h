#pragma once
#include"../gkpch.h"
#include"../GutKink/Core.h"
#include"Events/Event.h"
namespace EulerEngine {
	struct WindowInfo
	{
		float Width;
		float Height;
		std::string Title;
		WindowInfo(const std::string& title = "Euler Engine", float width = 1280.0f, float height = 900.0f) 
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
		
		virtual float getWIndowWidth() const = 0;
		virtual float getWindowHeight() const = 0;

		static EulerWindow* Create(const WindowInfo& info = WindowInfo());
	};
}