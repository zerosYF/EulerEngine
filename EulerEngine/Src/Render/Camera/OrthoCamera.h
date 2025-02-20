#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"EulerCamera.h"
namespace EulerEngine {
	class OrthoCamera :public EulerCamera{
	public:
		OrthoCamera(float aspectRatio = 1.0f, float nearClip = -1.0f, float farClip = 1.0f) :
			m_NearClip(nearClip), m_FarClip(farClip),
			EulerCamera(glm::ortho(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, nearClip, farClip), aspectRatio)
		{
		}
		virtual void UpdateProjection() override{
			m_ProjectionMatrix = glm::ortho(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, m_NearClip, m_FarClip);
		}

	private:
		float m_ZoomLevel = 1.0f;
		float m_NearClip = -1.0f;
		float m_FarClip = 1.0f;
	};
}