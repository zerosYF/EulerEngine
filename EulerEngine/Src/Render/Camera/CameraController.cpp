#include"gkpch.h"
#include"CameraController.h"
#include"Core/Input/EulerInput.h"
namespace EulerEngine{
	PerspectiveCameraController::PerspectiveCameraController()
	{
	}
	void PerspectiveCameraController::OnUpdate(TimerSystem ts)
	{
		if (InputSystem::IsKeyDown(KINK_KEY_A)) {

		}
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
		return false;
	}
	bool PerspectiveCameraController::OnWindowReized(WindowResizeEvent & e)
	{
		return false;
	}
}
