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
		if (InputSystem::IsKeyDown(KINK_KEY_W)) {
			Move(glm::vec3(0.0f, 1.0f * ts.GetDeltaTime(), 0.0f));
		}
		if (InputSystem::IsKeyDown(KINK_KEY_A)) {
			Move(glm::vec3(-1.0f * ts.GetDeltaTime(), 0.0f, 0.0f));
		}
		if (InputSystem::IsKeyDown(KINK_KEY_D)) {
			Move(glm::vec3(1.0f * ts.GetDeltaTime(), 0.0f, 0.0f));
		}
		if (InputSystem::IsKeyDown(KINK_KEY_S)) {
			Move(glm::vec3(0.0f, -1.0f * ts.GetDeltaTime(), 0.0f));
		}
		if (InputSystem::IsMouseBtnDown(KINK_MOUSE_BUTTON_LEFT)) {
			m_LeftBtn_Pressed = true;
		}
		else {
			m_LeftBtn_Pressed = false;
		}
		m_Camera->SetPosition(m_CameraPosition);
		m_Camera->SetRotation(m_CameraRotation);
	}
	void CameraController::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(KINK_BIND_EVENT_FUNC(CameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(KINK_BIND_EVENT_FUNC(CameraController::OnWindowReized));
		dispatcher.Dispatch<MouseMovedEvent>(KINK_BIND_EVENT_FUNC(CameraController::OnMouseMoved));
	}
	void CameraController::OnResize(float width, float height)
	{
	}
	bool CameraController::OnMouseScrolled(MouseScrolledEvent & e)
	{
		Zoom(e.GetYOffset() * 0.1f);
		return false;
	}
	bool CameraController::OnWindowReized(WindowResizeEvent & e)
	{
		return false;
	}
	bool CameraController::OnMouseMoved(MouseMovedEvent & e)
	{
		if (!m_LeftBtn_Pressed) {
			return false;
		}
		Rotate(glm::vec2(e.GetXOffset() * 10.0f , e.GetYOffset()) * 0.01f);
		return false;
	}
}
