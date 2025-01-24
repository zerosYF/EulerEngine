#pragma once
#include "Event.h"

namespace EulerEngine{
	class KINK_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(KINK_EVENT_CATEGORY_KEYBOARD | KINK_EVENT_CATEGORY_INPUT)
	protected:
		KeyEvent(int keycode) {
			this->m_KeyCode = keycode;
		}
		int m_KeyCode;
	};
	class KINK_API KeyPressedEvent :public KeyEvent {
	public:
		KeyPressedEvent(int keycode, unsigned int repeatCount) :KeyEvent(keycode){
			this->m_RepeatCount = repeatCount;
		}
		inline unsigned int GetRepeatedCount() const { return m_RepeatCount; }
		EVENT_CLASS_TYPE(KINK_KEY_PRESSED)
	private:
		unsigned int m_RepeatCount;
	};
	class KINK_API KeyReleasedEvent :public KeyEvent {
	public:
		KeyReleasedEvent(int keycode) :KeyEvent(keycode) {}
		EVENT_CLASS_TYPE(KINK_KEY_RELEASED)
	};
	class KINK_API KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keycode) :KeyEvent(keycode) {
		}
		EVENT_CLASS_TYPE(KINK_KEY_TYPED)
	};




	
	class KINK_API MouseMovedEvent : public Event {

	public:
		MouseMovedEvent(double x, double y, double xOffset, double yOffset) 
			: m_MouseX(x), m_MouseY(y), m_xOffset(xOffset), m_yOffset(yOffset){}
		inline double GetX() const { return m_MouseX; }
		inline double GetY() const { return m_MouseY; }
		inline double GetXOffset() const { return m_xOffset; }
		inline double GetYOffset() const { return m_yOffset; }
		EVENT_CLASS_TYPE(KINK_MOUSE_MOVED)
		EVENT_CLASS_CATEGORY(KINK_EVENT_CATEGORY_MOUSE | KINK_EVENT_CATEGORY_MOUSE)
	private:
		double m_MouseX;
		double m_MouseY;
		double m_xOffset;
		double m_yOffset;
	};
	class KINK_API MouseScrolledEvent :public Event {
	public:
		MouseScrolledEvent(double xOffset, double yOffset) :m_xOffset(xOffset), m_yOffset(yOffset) {}
		inline double GetXOffset() const { return m_xOffset; }
		inline double GetYOffset() const { return m_yOffset; }
		EVENT_CLASS_TYPE(KINK_MOUSE_SCROLLED)
		EVENT_CLASS_CATEGORY(KINK_EVENT_CATEGORY_MOUSE | KINK_EVENT_CATEGORY_INPUT)
	private:
		double m_xOffset;
		double m_yOffset;
	};
	class KINK_API MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const { return m_Button; }
		EVENT_CLASS_CATEGORY(KINK_EVENT_CATEGORY_MOUSE | KINK_EVENT_CATEGORY_INPUT)
	protected:
		MouseButtonEvent(int button) :m_Button(button) {}
		int m_Button;
	};
	class KINK_API MouseButtonPressedEvent :public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button) :MouseButtonEvent(button) {}
		EVENT_CLASS_TYPE(KINK_MOUSE_BUTTON_PRESSED)
	};
	class KINK_API MouseButtonReleasedEvent :public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button) :MouseButtonEvent(button) {}
		EVENT_CLASS_TYPE(KINK_MOUSE_BUTTON_RELEASED)
	};
}