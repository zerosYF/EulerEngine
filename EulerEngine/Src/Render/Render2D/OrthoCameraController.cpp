#include"gkpch.h"
#include"OrthoCameraController.h"
namespace EulerEngine {
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		:m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
		std::cout << m_AspectRatio << std::endl;
		std::cout << m_ZoomLevel << std::endl;
	}
	void OrthographicCameraController::OnUpdate(TimerSystem ts)
	{
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