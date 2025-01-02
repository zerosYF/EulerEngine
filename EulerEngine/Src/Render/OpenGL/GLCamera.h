#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include"../../Math/EulerMath.h"
#include<vector>
#include"../../Core/EulerTimer.h"
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

	//class Camera {
	//public:
	//	RenderCameraType m_cameraType = RenderCameraType::Editor;
	//	// 基本参数；
	//	glm::vec3 m_position{0.0f,0.0f,0.0f};
	//	glm::vec3 m_front{0.0f,0.0f,-1.0f};
	//	glm::vec3 m_up;
	//	glm::vec3 m_right;
	//	glm::vec3 m_worldUp;
	//	// 欧拉角；
	//	float m_yaw;
	//	float m_pitch;
	//	// 相机设置；
	//	float m_movementSpeed{SPEED};
	//	float m_movementSensitivity{SENSITIVITY};
	//	float m_fovAngle{FOV};

	//	// 向量初始化；
	//	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),float yaw = YAW, float pitch = PITCH) {
	//		m_position = position;
	//		m_worldUp = up;
	//		m_yaw = yaw;
	//		m_pitch = pitch;
	//		updateCameraVectors();
	//	}
	//	// 标量初始化；
	//	Camera(float PosX, float PosY, float PosZ, float UpX, float UpY, float UpZ, float yaw, float pitch) {
	//		m_position = glm::vec3(PosX, PosY, PosZ);
	//		m_worldUp = glm::vec3(UpX, UpY, UpZ);
	//		m_yaw = yaw;
	//		m_pitch = pitch;
	//		updateCameraVectors();
	//	}
	//	glm::mat4 GetViewMatrix() {
	//		return lookAt(m_position, m_position + m_front, m_up);
	//	}
	//	void move(glm::vec3 delta) {
	//		m_position += delta;
	//	}
	//	void rotate(glm::vec2 delta) {
	//		m_pitch += SENSITIVITY*	delta.x;
	//		m_yaw += SENSITIVITY * delta.y;
	//	}
	//	void zoom(float offset) {
	//		m_fovAngle = glm::clamp(m_fovAngle - offset,MIN_FOV,MAX_FOV);
	//	}

	//private:
	//	void updateCameraVectors() {
	//		glm::vec3 front{ glm::cos(glm::radians(m_yaw))*glm::cos(glm::radians(m_pitch)) ,
	//							glm::sin(glm::radians(m_pitch)),
	//							glm::sin(glm::radians(m_yaw))*glm::cos(glm::radians(m_pitch)) };
	//		m_front = glm::normalize(front);
	//		m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	//		m_up = glm::normalize(cross(m_right, m_front));
	//	}
	//};
}
#endif // CAMERA_H
