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
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};
	const float YAW = -90.0f;//ƫ���ǣ�
	const float PITCH = 0.0f;//�����ǣ�
	const float SPEED = 2.5f;//�ٶȣ�
	const float SENSITIVITY = 0.1f;//���жȣ�
	const float FOV = 45.0f;//�佹�нǣ�
	const float MIN_FOV = 10.0F;
	const float MAX_FOV = 89.0f;

	class PerspectiveCamera {
	public:
		RenderCameraType m_cameraType = RenderCameraType::Editor;
		// ����������
		glm::vec3 m_Position{ 0.0f,0.0f,0.0f };
		glm::vec3 m_Front{ 0.0f,0.0f,-1.0f };
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;
		// ŷ���ǣ�
		float m_Yaw;
		float m_Pitch;
		// ������ã�
		float m_MovementSpeed{ SPEED };
		float m_MovementSensitivity{ SENSITIVITY };
		float m_FovAngle{ FOV };
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
	public:
		// ������ʼ����
		PerspectiveCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) :
			m_ProjectionMatrix(glm::perspective(glm::radians(m_FovAngle), 1.0f, 0.1f, 100.0f)) {
			m_Position = position;
			m_WorldUp = up;
			m_Yaw = yaw;
			m_Pitch = pitch;
			UpdateCameraVectors();
		}
		// ������ʼ����
		PerspectiveCamera(float PosX, float PosY, float PosZ, float UpX, float UpY, float UpZ, float yaw, float pitch) {
			m_Position = glm::vec3(PosX, PosY, PosZ);
			m_WorldUp = glm::vec3(UpX, UpY, UpZ);
			m_Yaw = yaw;
			m_Pitch = pitch;
			UpdateCameraVectors();
		}
		glm::mat4 GetViewMatrix() {
			return m_ViewMatrix;
		}
		glm::mat4 LookAt(glm::vec3 target, glm::vec3 up, glm::vec3 position) {
			return m_ViewMatrix;
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
		void OnUpdate(TimerSystem ts) {

		}
		void OnEvent(Event& e) {
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
		void UpdateViewMatrix() {
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position)
				* glm::rotate(glm::mat4(1.0f), m_Yaw, glm::vec3(0, 0, 1));
			m_ViewMatrix = glm::inverse(transform);
		}
		void UpdateProjectionMatrix() {

		}
	};
}
