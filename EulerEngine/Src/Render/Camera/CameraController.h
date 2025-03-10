#pragma once
#include"Core/Events/Event.h"
#include"Core/Events/InputEvent.h"
#include"Core/Events/ApplicationEvent.h"
#include"Core/EulerTimer.h"
#include"EulerCamera.h"
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
		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;
		inline void Pan(glm::vec2 delta) {
			auto [xSpeed, ySpeed] = PanSpeed();
			m_FocalPoint += -m_Camera->GetRight() * delta.x * xSpeed * m_Distance;
			m_FocalPoint += m_Camera->GetUp() * delta.y * ySpeed * m_Distance;
		}
		inline void Zoom(float delta) {
			m_Distance -= delta * ZoomSpeed();
			if (m_Distance < 1.0f) {
				m_FocalPoint += m_Camera->GetFront();
				m_Distance = 1.0f;
			}
		}
		inline void Rotate(glm::vec2 delta) {
			float yawSign = m_Camera->GetUp().y < 0? -1.0f : 1.0f;
			m_CameraRotation.y += delta.x * RotationSpeed();
			m_CameraRotation.x -= delta.y * RotationSpeed() * yawSign;
		}
		inline void CalculatePosition() {
			m_CameraPosition = m_FocalPoint - m_Camera->GetFront() * m_Distance;
		}
	private:
		Ref<EulerCamera> m_Camera;
		glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_CameraRotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec2 m_LastMousePosition = glm::vec2(0.0f, 0.0f);
		float m_Distance = 5.0f;
		glm::vec3 m_FocalPoint = glm::vec3(0.0f, 0.0f, 0.0f);
	};
}
