#pragma once
#include"gkpch.h"
#include"Core/EulerTimer.h"
#include"Core/Events/Event.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
namespace EulerEngine {
	enum RenderCameraType {
		Editor,
		Motor,
	};
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float FOV = 45.0f;
	const float MIN_FOV = 10.0F;
	const float MAX_FOV = 89.0f;

	class PerspectiveCamera {
	public:
		RenderCameraType m_cameraType = RenderCameraType::Editor;
		glm::vec3 m_Position{ 0.0f,0.0f,0.0f };
		glm::vec3 m_Front{ 0.0f,0.0f,-1.0f };
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;
		float m_Yaw;
		float m_Pitch;
		float m_MovementSpeed{ SPEED };
		float m_MovementSensitivity{ SENSITIVITY };
		float m_FovAngle{ FOV };
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
	public:
		PerspectiveCamera(
			glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), 
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), 
			float yaw = YAW, float pitch = PITCH) :
			m_ProjectionMatrix(glm::perspective(glm::radians(m_FovAngle), 1.0f, 0.1f, 100.0f)),
			m_ViewMatrix(glm::lookAt(m_Position, m_Position + m_Front, m_Up)){
			m_Position = position;
			m_WorldUp = up;
			m_Yaw = yaw;
			m_Pitch = pitch;
			UpdateCameraVectors();
		}
		glm::mat4 GetViewMatrix() {
			return m_ViewMatrix;
		}
		glm::mat4 GetProjectionMatrix() {
			return m_ProjectionMatrix;
		}
		void Move(glm::vec3 delta) {
			m_Position += delta;
		}
		void Rotate(glm::vec2 delta) {
			m_Pitch += SENSITIVITY * delta.x;
			m_Yaw += SENSITIVITY * delta.y;
		}
		void Zoom(float offset) {
			m_FovAngle = glm::clamp(m_FovAngle - offset, MIN_FOV, MAX_FOV);
		}

		void UpdateViewMatrix() {
			m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		}
		void UpdateProjectionMatrix() {
			m_ProjectionMatrix = glm::perspective(glm::radians(m_FovAngle), 1.0f, 0.1f, 100.0f);
		}

	private:
		void UpdateCameraVectors() {
			glm::vec3 front{ glm::cos(glm::radians(m_Yaw))*glm::cos(glm::radians(m_Pitch)) ,
								glm::sin(glm::radians(m_Pitch)),
								glm::sin(glm::radians(m_Yaw))*glm::cos(glm::radians(m_Pitch)) };
			m_Front = glm::normalize(front);
			m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
			m_Up = glm::normalize(cross(m_Right, m_Front));
		}
	};
}
