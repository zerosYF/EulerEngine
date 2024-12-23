#pragma once
#include "../Core/Layer/EulerLayer.h"
#include "../Core/Events/InputEvent.h"
#include "../Core/Events/ApplicationEvent.h"
namespace EulerEngine {
	class KINK_API ImGuiLayer :public EulerLayer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);
	private:
		bool OnMouseBtnDown(MouseButtonPressedEvent& e);
		bool OnMouseBtnUp(MouseButtonReleasedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnKeyDown(KeyPressedEvent& e);
		bool OnKeyUp(KeyReleasedEvent& e);
		bool OnKey(KeyTypedEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}