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
	EulerEngine::PerspectiveCamera m_Camera;
	EulerEngine::Ref<EulerEngine::VertexArray> m_VertexArray;
	EulerEngine::Ref<EulerEngine::EulerShader> m_Shader;
	EulerEngine::Ref<EulerEngine::Texture2D> m_Texture2D;
	EulerEngine::ResourceLibrary m_ResourceLib;
	glm::vec4 m_Color = {0.2f, 0.3f, 0.1f, 1.0f};
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraSpeed = 5.0f;
};
