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





	
	class KINK_API MouseMovedEvent : public Event {

	public:
		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y){}
		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }
		EVENT_CLASS_TYPE(KINK_MOUSE_MOVED)
		EVENT_CLASS_CATEGORY(KINK_EVENT_CATEGORY_MOUSE | KINK_EVENT_CATEGORY_MOUSE)
	private:
		float m_MouseX;
		float m_MouseY;
	};
	class KINK_API MouseScrolledEvent :public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset) :m_xOffset(xOffset), m_yOffset(yOffset) {}
		inline float GetXOffset() const { return m_xOffset; }
		inline float GetyOffset() const { return m_yOffset; }
		EVENT_CLASS_TYPE(KINK_MOUSE_SCROLLED)
		EVENT_CLASS_CATEGORY(KINK_EVENT_CATEGORY_MOUSE | KINK_EVENT_CATEGORY_INPUT)
	private:
		float m_xOffset;
		float m_yOffset;
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