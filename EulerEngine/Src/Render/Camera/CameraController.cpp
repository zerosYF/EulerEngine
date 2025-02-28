#include"gkpch.h"
#include"CameraController.h"
#include"Core/Input/EulerInput.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine{
	CameraController::CameraController(CameraType type)
	{
		m_Camera = CreateRef<EulerCamera>(type);
	}
	void CameraController::OnUpdate(TimerSystem ts)
	{
		if (InputSystem::IsKeyDown(KINK_KEY_LEFT_ALT)) {
			const glm::vec2& mouse{ InputSystem::GetCursorPosition().first, InputSystem::GetCursorPosition().second };
			glm::vec2 delta = (mouse - m_LastMousePosition) * 0.003f;
			m_LastMousePosition = mouse;

			if (InputSystem::IsMouseBtnDown(KINK_MOUSE_BUTTON_MIDDLE)) {
				Pan(delta);
				//KINK_CORE_INFO("PAN:{0}, {1}, {2}", m_CameraPosition.x, m_CameraPosition.y, m_CameraPosition.z);
			}
			else if (InputSystem::IsMouseBtnDown(KINK_MOUSE_BUTTON_LEFT)) {
				Rotate(delta);
			}
			else if (InputSystem::IsMouseBtnDown(KINK_MOUSE_BUTTON_RIGHT)) {
				Zoom(delta.y);
			}

		}
		CalculatePosition();
		m_Camera->SetPosition(m_CameraPosition);
		m_Camera->SetRotation(glm::radians(m_CameraRotation));
	}
	void CameraController::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(KINK_BIND_EVENT_FUNC(CameraController::OnMouseScrolled));
	}
	void CameraController::OnResize(float width, float height)
	{
		m_Camera->SetViewportSize(width, height);
	}
	bool CameraController::OnMouseScrolled(MouseScrolledEvent & e)
	{
		Zoom(e.GetYOffset() * 0.1f);
		return false;
	}
	std::pair<float, float> CameraController::PanSpeed() const
	{
		float x = std::min(m_Camera->GetViewportSize().first / 1000.0f, 2.4f);
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;
		float y = std::min(m_Camera->GetViewportSize().second / 1000.0f, 2.4f);
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;
		return std::pair<float, float>(xFactor, yFactor);
	}
	float CameraController::RotationSpeed() const
	{
		return 4.0f;
	}
	float CameraController::ZoomSpeed() const
	{
		float distance = m_Distance * 0.2f;
		distance = std::max(distance, 0.0f);
		float speed = distance * distance;
		speed = std::min(speed, 100.0f);
		return speed;
	}
}
