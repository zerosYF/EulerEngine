#pragma once
#include"GutKink.h"
class TestLayer :public EulerEngine::EulerLayer{
public:
	TestLayer();
	virtual ~TestLayer() = default;
	virtual void OnDetach() override;
	virtual void OnAttach() override;
	virtual void OnUpdate(EulerEngine::TimerSystem ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(EulerEngine::Event& e) override;
private:
	EulerEngine::PerspectiveCameraController m_CameraController;
	EulerEngine::Ref<EulerEngine::VertexArray> m_VertexArray;
	EulerEngine::ResourceLibrary m_ResourceLib;
	glm::vec4 m_Color = {0.2f, 0.3f, 0.1f, 1.0f};
	glm::vec3 m_CubePositions[10] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	EulerEngine::Ref<EulerEngine::Texture2D> m_Test_Texture;
	EulerEngine::Ref<EulerEngine::Material> m_Test_Material;
};
