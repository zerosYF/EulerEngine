#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include"../../Math/EulerMath.h"
#include<vector>
#include"../../Core/EulerTimer.h"
namespace EulerEngine {
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

	class Camera {
	public:
		// 基本参数；
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;
		// 欧拉角；
		float Yaw;
		float Pitch;
		// 相机设置；
		float MovementSpeed;
		float MovementSensitivity;
		float Fov_Angle;

		// 向量初始化；
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
			float yaw = YAW, float pitch = PITCH) {
			Position = position;
			WorldUp = up;
			Yaw = yaw;
			Pitch = pitch;

			Front = glm::vec3(0.0f, 0.0f, -1.0f);
			MovementSpeed = SPEED;
			MovementSensitivity = SENSITIVITY;
			Fov_Angle = FOV;
			updateCameraVectors();
		}
		// 标量初始化；
		Camera(float PosX, float PosY, float PosZ, float UpX, float UpY, float UpZ, float yaw, float pitch) {
			Position = glm::vec3(PosX, PosY, PosZ);
			WorldUp = glm::vec3(UpX, UpY, UpZ);
			Yaw = yaw;
			Pitch = pitch;

			Front = glm::vec3(0.0f, 0.0f, -1.0f);
			MovementSpeed = SPEED;
			MovementSensitivity = SENSITIVITY;
			Fov_Angle = FOV;
			updateCameraVectors();
		}
		glm::mat4 GetViewMatrix() {
			return glm::lookAt(Position, Position + Front, Up);
		}

		void ProcessKeyboard(Camera_Movement direction) {
			float vel = MovementSpeed * (TimerManager::GetInstance()->GetDeltaTime());
			if (direction == FORWARD) {
				Position += Front * vel;
			}
			if (direction == BACKWARD) {
				Position -= Front * vel;
			}
			if (direction == LEFT) {
				Position -= Right * vel;
			}
			if (direction == RIGHT) {
				Position += Right * vel;
			}
		}

		void ProcessMouseMovement(float Xoffset, float Yoffset, bool constrainPitch = true) {
			Xoffset *= MovementSensitivity;
			Yoffset *= MovementSensitivity;

			Yaw += Xoffset;
			Pitch += Yoffset;

			if (constrainPitch) {
				if (Pitch > 89.0f) {
					Pitch = 89.0f;
				}
				else if (Pitch < -89.0f) {
					Pitch = -89.0f;
				}
			}
			updateCameraVectors();
		}

		void ProcessMouseScroll(float Yoffset) {
			if (Fov_Angle >= 1.0f &&Fov_Angle <= 45.0f) {
				Fov_Angle -= Yoffset;
			}
			else if (Fov_Angle <= 1.0f) {
				Fov_Angle = 1.0f;
			}
			else if (Fov_Angle >= 45.0f) {
				Fov_Angle = 45.0f;
			}
		}

	private:
		void updateCameraVectors() {
			glm::vec3 front;
			front.x = cos(glm::radians(Yaw))*cos(glm::radians(Pitch));
			front.y = sin(glm::radians(Pitch));
			front.z = sin(glm::radians(Yaw))*cos(glm::radians(Pitch));
			Front = glm::normalize(front);
			Right = glm::normalize(glm::cross(Front, WorldUp));
			Up = glm::normalize(glm::cross(Right, Front));
		}
	};
}
#endif // CAMERA_H
