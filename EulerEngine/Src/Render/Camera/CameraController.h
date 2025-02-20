#pragma once
#include"PerspectiveCamera.h"
#include"Core/Events/Event.h"
#include"Core/Events/InputEvent.h"
#include"Core/Events/ApplicationEvent.h"
#include"Core/EulerTimer.h"
namespace EulerEngine {
	class CameraController {
	public:
		CameraController(CameraType type);
		void OnUpdate(TimerSystem ts);
		void OnEvent(Event& e);
		void OnResize(float width, float height);
		Ref<EulerCamera>& GetCamera() { return m_Camera; }
		const Ref<EulerCamera>& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowReized(WindowResizeEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		inline void Move(glm::vec3 delta) {
			m_CameraPosition += delta * SPEED;
		}
		inline void Zoom(float delta) {
			m_CameraPosition.z -= delta * SPEED;
		}
		inline void Rotate(glm::vec2 delta) {
			m_CameraRotation.x -= delta.y * SPEED;
			m_CameraRotation.y += delta.x * SPEED;
		}
	private:
		Ref<EulerCamera> m_Camera;
		CameraType m_CameraType = CameraType::PERSPECTIVE;
		glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 m_CameraRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		bool m_LeftBtn_Pressed = false;
	};
}
