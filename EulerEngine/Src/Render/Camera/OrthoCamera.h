#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include"EulerCamera.h"
namespace EulerEngine {
	class OrthoCamera :public EulerCamera{
	public:
		OrthoCamera(float left = -1.0f, float right = 1.0f, float top = 1.0f, float bottom = -1.0f, float near = -1.0f, float far = 1.0f) :
			m_Left(left), m_Right(right), m_Bottom(bottom), m_Top(top), m_Near(near), m_Far(far),
			EulerCamera(glm::ortho(m_Left, m_Right, m_Bottom, m_Top, m_Near, m_Far))
		{
		}
		virtual void UpdateProjection() override{
			m_ProjectionMatrix = glm::ortho(m_Left, m_Right, m_Bottom, m_Top, -1.0f, 1.0f);
		}

	private:
		float m_Left = -1.0f;
		float m_Right = 1.0f;
		float m_Bottom = -1.0f;
		float m_Top = 1.0f;
		float m_Near = -1.0f;
		float m_Far = 1.0f;
	};
}