#include"gkpch.h"
#include"OrthoCameraController.h"
namespace EulerEngine {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}
	void OrthographicCameraController::OnUpdate(TimerSystem ts)
	{
		m_Camera.CalViewMatrix();
	}
	void OrthographicCameraController::OnEvent(Event& e)
	{
	}
	void OrthographicCameraController::OnResize(float width, float height)
	{
	}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		return false;
	}
	bool OrthographicCameraController::OnWindowReized(WindowResizeEvent& e)
	{
		return false;
	}
	bool OrthographicCameraController::OnMouseMoved(MouseMovedEvent& e)
	{
		return false;
	}
}