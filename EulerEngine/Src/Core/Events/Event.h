#pragma once
#include"../../GutKink/Core.h"
namespace EulerEngine{
	enum class EventType {
		None = 0,
		KINK_WINDOW_CLOSE,
		KINK_WINDOW_RESIZE,
		KINK_WINDOW_FOCUS,
		KINK_WINDOW_LOSE_FOCUS,
		KINK_WINDOW_MOVED,

		KINK_APP_TICK,
		KINK_APP_UPDATE,
		KINK_APP_RENDER,

		KINK_KEY_PRESSED,
		KINK_KEY_RELEASED,
		KINK_KEY_TYPED,

		KINK_MOUSE_BUTTON_PRESSED,
		KINK_MOUSE_BUTTON_RELEASED,
		KINK_MOUSE_SCROLLED,
		KINK_MOUSE_MOVED,
	};
	enum EventCategory {
		None = 0,
		KINK_EVENT_CATEGORY_APPLICATION = BIT(0),
		KINK_EVENT_CATEGORY_INPUT = BIT(1),
		KINK_EVENT_CATEGORY_KEYBOARD = BIT(2),
		KINK_EVENT_CATEGORY_MOUSE = BIT(3),
		KINK_EVENT_CATEGORY_MOUSE_BUTTON = BIT(4)
	};
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
	class KINK_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName();  }
		virtual bool IsHandled() const { return m_Handled; }
		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};
	class EventDispatcher {
		template<typename T>
		using EventFunc = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) :m_Event(event){
		}
		template<typename T>
		bool Dispatch(EventFunc<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}