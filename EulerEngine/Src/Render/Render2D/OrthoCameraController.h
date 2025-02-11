#pragma once
#include"Core/Events/Event.h"
#include"Core/Events/InputEvent.h"
#include"Core/Events/ApplicationEvent.h"
#include"Core/EulerTimer.h"
#include"OrthoCamera.h"
namespace EulerEngine {
	class OrthographicCameraController {
	public:
		OrthographicCameraController(float aspectRitio, bool rotation);
		void OnUpdate(TimerSystem ts);
		void OnEvent(Event& e);
		void OnResize(float width, float height);
		OrthoCamera& GetCamera() { return m_Camera; }
		const OrthoCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowReized(WindowResizeEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
	private:
		OrthoCamera m_Camera;
		bool m_LeftBtn_Pressed = false;
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		bool m_Rotation;

		glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
		float m_CameraRotation = 0.0f;
	};
}