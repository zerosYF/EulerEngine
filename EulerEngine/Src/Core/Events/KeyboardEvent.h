#pragma once
#include"Event.h"
namespace EulerEngine {
	class KINK_API KeyboardEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(KINK_EVENT_CATEGORY_KEYBOARD | KINK_EVENT_CATEGORY_INPUT)
	protected:
		KeyboardEvent(int keycode) {
			this->m_KeyCode = keycode;
		}
		int m_KeyCode;
	};
	class KINK_API KeyPressedEvent :public KeyboardEvent {
	public:
		KeyPressedEvent(int keycode, unsigned int repeatCount) :KeyboardEvent(keycode) {
			this->m_RepeatCount = repeatCount;
		}
		inline unsigned int GetRepeatedCount() const { return m_RepeatCount; }
		EVENT_CLASS_TYPE(KINK_KEY_PRESSED)
	private:
		unsigned int m_RepeatCount;
	};
	class KINK_API KeyReleasedEvent :public KeyboardEvent {
	public:
		KeyReleasedEvent(int keycode) :KeyboardEvent(keycode) {}
		EVENT_CLASS_TYPE(KINK_KEY_RELEASED)
	};
	class KINK_API KeyTypedEvent : public KeyboardEvent {
	public:
		KeyTypedEvent(int keycode) :KeyboardEvent(keycode) {
		}
		EVENT_CLASS_TYPE(KINK_KEY_TYPED)
	};
}