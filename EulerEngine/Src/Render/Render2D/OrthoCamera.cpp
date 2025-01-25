#include"gkpch.h"
#include"OrthoCamera.h"
#include <glm/gtc/matrix_transform.hpp>
namespace EulerEngine {
	OrthoCamera::OrthoCamera(float left, float right, float top, float bottom):
		m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
	}
	void OrthoCamera::SetProjection(float left, float right, float top, float bottom)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	}
	void OrthoCamera::CalViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transform);
	}
}