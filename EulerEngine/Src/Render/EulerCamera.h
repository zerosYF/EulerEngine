#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include"gkpch.h"
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
	const float YAW = -90.0f;//偏航角；
	const float PITCH = 0.0f;//俯仰角；
	const float SPEED = 2.5f;//速度；
	const float SENSITIVITY = 0.1f;//敏感度；
	const float FOV = 45.0f;//变焦夹角；
	const float MIN_FOV = 10.0F;
	const float MAX_FOV = 89.0f;

	class Camera {
	public:
		RenderCameraType m_cameraType = RenderCameraType::Editor;
		// 基本参数；
		glm::vec3 m_Position{0.0f,0.0f,0.0f};
		glm::vec3 m_Front{0.0f,0.0f,-1.0f};
		glm::vec3 m_Up;
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp;
		// 欧拉角；
		float m_Yaw;
		float m_Pitch;
		// 相机设置；
		float m_MovementSpeed{SPEED};
		float m_MovementSensitivity{SENSITIVITY};
		float m_FovAngle{FOV};
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
	public:
		// 向量初始化；
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),float yaw = YAW, float pitch = PITCH):
			m_ProjectionMatrix(glm::perspective(glm::radians(m_FovAngle), 1.0f, 0.1f, 100.0f)){
			m_Position = position;
			m_WorldUp = up;
			m_Yaw = yaw;
			m_Pitch = pitch;
			UpdateCameraVectors();
		}
		// 标量初始化；
		Camera(float PosX, float PosY, float PosZ, float UpX, float UpY, float UpZ, float yaw, float pitch) {
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
			m_Pitch += SENSITIVITY*	delta.x;
			m_Yaw += SENSITIVITY * delta.y;
		}
		void Zoom(float offset) {
			m_FovAngle = glm::clamp(m_FovAngle - offset,MIN_FOV,MAX_FOV);
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
			glm::mat4 transform = glm::translate(glm::mat4(1.0f),m_Position) 
				* glm::rotate(glm::mat4(1.0f), m_Yaw, glm::vec3(0, 0, 1));
			m_ViewMatrix = glm::inverse(transform);
		}
		void UpdateProjectionMatrix() {
		
		}
	};
}
#endif // CAMERA_H
