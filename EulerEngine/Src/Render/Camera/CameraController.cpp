#include"gkpch.h"
#include"CameraController.h"
#include"Core/Input/EulerInput.h"
namespace EulerEngine{
	PerspectiveCameraController::PerspectiveCameraController():m_Camera()
	{
	}
	void PerspectiveCameraController::OnUpdate(TimerSystem ts)
	{
		if (InputSystem::IsKeyDown(KINK_KEY_W)) {
			m_Camera.Move(glm::vec3(0.0f, 0.0f, -1.0f));
		}
		if (InputSystem::IsKeyDown(KINK_KEY_A)) {
			m_Camera.Move(glm::vec3(0.0f, -1.0f, 0.0f));
		}
		if (InputSystem::IsKeyDown(KINK_KEY_D)) {
			m_Camera.Move(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (InputSystem::IsKeyDown(KINK_KEY_S)) {
			m_Camera.Move(glm::vec3(0.0f, 0.0f, 1.0f));
		}
		m_Camera.UpdateProjectionMatrix();
		m_Camera.UpdateViewMatrix();
		m_Camera.UpdateCameraVectors();
	}
	void PerspectiveCameraController::OnEvent(Event & e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(KINK_BIND_EVENT_FUNC(PerspectiveCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(KINK_BIND_EVENT_FUNC(PerspectiveCameraController::OnWindowReized));
	}
	void PerspectiveCameraController::OnResize(float width, float height)
	{
	}
	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent & e)
	{
		m_Camera.Zoom(1.0f);
		return false;
	}
	bool PerspectiveCameraController::OnWindowReized(WindowResizeEvent & e)
	{
		return false;
	}
	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent & e)
	{
		m_Camera.Rotate(glm::vec2(e.GetXOffset(), e.GetYOffset()));
		return false;
	}
}
