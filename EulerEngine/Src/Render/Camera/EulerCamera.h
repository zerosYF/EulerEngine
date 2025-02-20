#pragma once
#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
#include"GutKink/Core.h"
namespace EulerEngine {
	enum CameraType {
		PERSPECTIVE,
		ORTHOGRAPHIC,
	};
	class EulerCamera {
	public:
		EulerCamera(glm::mat4 projectionMatrix)
			:m_ProjectionMatrix(projectionMatrix) {
			UpdateView();
		}
		glm::mat4 GetProjectionMatrix() {
			UpdateProjection();
			return m_ProjectionMatrix;
		}
		glm::mat4 GetViewMatrix() {
			return m_ViewMatrix;
		}


		const glm::vec3& GetPosition() const {
			return m_Position;
		}
		const void SetPosition(const glm::vec3& position) {
			m_Position = position;
			UpdateView();
		}
		const glm::vec3& GetRotation() const {
			return m_Rotation;
		}
		const void SetRotation(const glm::vec3& rotation) {
			m_Rotation = rotation + glm::vec3(0.0f, -90.0f, 0.0f);
			UpdateView();
		}

		static Ref<EulerCamera> Create(CameraType type);
	protected:
		virtual void UpdateView() {
			float yaw = m_Rotation.y;
			float pitch = m_Rotation.x;
			m_Front = {
				glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch)),
				glm::sin(pitch),
				glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch))
			};
			m_Front = glm::normalize(m_Front);
			m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
			m_Up = glm::normalize(cross(m_Right, m_Front));
			m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		}
	public:
		virtual void UpdateProjection() = 0;
	protected:
		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f, -90.0f, 0.0f);

		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_Right;
		glm::vec3 m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
	};
}