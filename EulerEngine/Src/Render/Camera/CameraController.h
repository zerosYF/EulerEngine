#pragma once
#include"EulerCamera.h"
#include"Core/Events/Event.h"
#include"Core/Events/InputEvent.h"
#include"Core/Events/ApplicationEvent.h"
#include"Core/EulerTimer.h"
namespace EulerEngine {
	class PerspectiveCameraController {
	public:
		PerspectiveCameraController();
		void OnUpdate(TimerSystem ts);
		void OnEvent(Event& e);
		void OnResize(float width, float height);
		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowReized(WindowResizeEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
	private:
		PerspectiveCamera m_Camera;
		bool m_LeftBtn_Pressed = false;
	};
}
