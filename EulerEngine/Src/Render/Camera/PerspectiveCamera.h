#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"EulerCamera.h"
namespace EulerEngine {
	const float SPEED = 0.7f;
	const float FOV = 45.0f;
	const float MIN_FOV = 10.0F;
	const float MAX_FOV = 89.0f;

	class PerspectiveCamera:public EulerCamera {
	private:
		float m_FovAngle;
		float m_AspectRatio;
		float m_NearClip;
		float m_FarClip;
	public:
		PerspectiveCamera(float fov = FOV, float aspectRatio = 1.0f, float nearClip = 0.1f, float farClip = 100.0f) :
			m_FovAngle(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip),
			EulerCamera(glm::perspective(glm::radians(m_FovAngle), m_AspectRatio, m_NearClip, m_FarClip)){
		}
		virtual void UpdateProjection() override{
			m_ProjectionMatrix = glm::perspective(glm::radians(m_FovAngle), m_AspectRatio, m_NearClip, m_FarClip);
		}
	};
}
