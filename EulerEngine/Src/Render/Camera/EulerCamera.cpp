#include"gkpch.h"
#include"EulerCamera.h"
namespace EulerEngine {
	void EulerCamera::UpdateView() {
		float yaw = m_Rotation.y;
		float pitch = m_Rotation.x;
		float roll = m_Rotation.z;
		m_Front = {
			glm::cos(yaw) * glm::cos(pitch),
			glm::sin(pitch),
			glm::sin(yaw) * glm::cos(pitch)
		};
		m_Front = glm::normalize(m_Front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(cross(m_Right, m_Front));
		//roll
		glm::mat3 rotateRoll = glm::rotate(glm::mat4(1.0f), roll, m_Front);
		m_Right = rotateRoll * m_Right;
		m_Up = rotateRoll * m_Up;
		m_Front = glm::cross(m_Up, m_Right);

		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}
	void EulerCamera::UpdateProjection(){
		if (m_ProjectionType == CameraType::PERSPECTIVE) {
			m_ProjectionMatrix = glm::perspective(glm::radians(m_PerspectiveCameraData.FovAngle), m_AspectRatio, m_PerspectiveCameraData.NearClip, m_PerspectiveCameraData.FarClip);
		}
		else if (m_ProjectionType == CameraType::ORTHOGRAPHIC) {
			float orthoSize = m_OrthographicCameraData.ZoomLevel * m_AspectRatio;
			m_ProjectionMatrix = glm::ortho(-orthoSize, orthoSize, -m_OrthographicCameraData.ZoomLevel, m_OrthographicCameraData.ZoomLevel, m_OrthographicCameraData.NearClip, m_OrthographicCameraData.FarClip);
		}
	}
}