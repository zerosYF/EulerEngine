#include"gkpch.h"
#include"CameraController.h"
#include"Core/Input/EulerInput.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine{
	PerspectiveCameraController::PerspectiveCameraController():m_Camera()
	{
	}
	void PerspectiveCameraController::OnUpdate(TimerSystem ts)
	{
		if (InputSystem::IsKeyDown(KINK_KEY_W)) {
			m_Camera.Move(glm::vec3(0.0f, 1.0f * ts.GetDeltaTime(), 0.0f));
		}
		if (InputSystem::IsKeyDown(KINK_KEY_A)) {
			m_Camera.Move(glm::vec3(-1.0f * ts.GetDeltaTime(), 0.0f, 0.0f));
		}
		if (InputSystem::IsKeyDown(KINK_KEY_D)) {
			m_Camera.Move(glm::vec3(1.0f * ts.GetDeltaTime(), 0.0f, 0.0f));
		}
		if (InputSystem::IsKeyDown(KINK_KEY_S)) {
			m_Camera.Move(glm::vec3(0.0f, -1.0f * ts.GetDeltaTime(), 0.0f));
		}
		if (InputSystem::IsMouseBtnDown(KINK_MOUSE_BUTTON_LEFT)) {
			m_LeftBtn_Pressed = true;
		}
		else {
			m_LeftBtn_Pressed = false;
		}
		m_Camera.UpdateProjectionMatrix();
		m_Camera.UpdateViewMatrix();
	}
	void PerspectiveCameraController::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(KINK_BIND_EVENT_FUNC(PerspectiveCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(KINK_BIND_EVENT_FUNC(PerspectiveCameraController::OnWindowReized));
		dispatcher.Dispatch<MouseMovedEvent>(KINK_BIND_EVENT_FUNC(PerspectiveCameraController::OnMouseMoved));
	}
	void PerspectiveCameraController::OnResize(float width, float height)
	{
	}
	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent & e)
	{
		m_Camera.Zoom(e.GetYOffset());
		return false;
	}
	bool PerspectiveCameraController::OnWindowReized(WindowResizeEvent & e)
	{
		return false;
	}
	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent & e)
	{
		if (!m_LeftBtn_Pressed) {
			return false;
		}
		m_Camera.Rotate(glm::vec2(e.GetXOffset(), e.GetYOffset()));
		m_Camera.UpdateCameraVectors();
		return false;
	}
}
