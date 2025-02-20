#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"EulerCamera.h"
namespace EulerEngine {
	class OrthoCamera :public EulerCamera{
	public:
		OrthoCamera(float left = -1.0f, float right = 1.0f, float top = 1.0f, float bottom = -1.0f, float nearClip = -1.0f, float farClip = 1.0f) :
			m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top), m_NearClip(nearClip), m_FarClip(farClip),
			EulerCamera(glm::ortho(left, right, bottom, top, nearClip, farClip))
		{
		}
		virtual void UpdateProjection() override{
			m_ProjectionMatrix = glm::ortho(m_Left, m_Right, m_Bottom, m_Top, m_NearClip, m_FarClip);
		}

	private:
		float m_Left = -1.0f;
		float m_Right = 1.0f;
		float m_Bottom = -1.0f;
		float m_Top = 1.0f;
		float m_NearClip = -1.0f;
		float m_FarClip = 1.0f;
	};
}