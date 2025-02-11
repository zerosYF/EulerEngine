#pragma once
#include<glm/glm.hpp>
namespace EulerEngine {
	class OrthoCamera {
	public:
		OrthoCamera(float left, float right, float top, float bottom);
		void SetProjection(float left, float right, float top, float bottom);
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(glm::vec3& position) { m_Position = position; CalViewMatrix(); }
		const float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; CalViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() { return m_ViewMatrix; }
		void CalViewMatrix();
	private:
		glm::vec3 m_Position = {0.0f, 0.0f, 0.0f};
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		float m_Rotation = 0.0f;
	};
}