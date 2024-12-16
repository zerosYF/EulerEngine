#pragma once
#include "Event.h"
#include <sstream>

namespace EulerEngine{
	class KINK_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height): m_Width(width), m_Height(height){
		
		}
		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent:" << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WINDOW_RESIZE)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	private:
		unsigned int m_Width;
		unsigned int m_Height;
	};
	class KINK_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}
		EVENT_CLASS_TYPE(WINDOW_CLOSE)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};
	class KINK_API AppTickEvent : public Event {
	public:
		AppTickEvent() {}
		EVENT_CLASS_TYPE(APP_TICK)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};
	class KINK_API AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() {}
		EVENT_CLASS_TYPE(APP_UPDATE)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};
	class KINK_API AppRenderEvent : public Event {
	public:
		AppRenderEvent() {}
		EVENT_CLASS_TYPE(APP_RENDER)
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION)
	};

}