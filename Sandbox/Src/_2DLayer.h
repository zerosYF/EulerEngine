#pragma once
#include"GutKink.h"
class _2DLayer :public EulerEngine::EulerLayer {
public:
	_2DLayer();
	virtual ~_2DLayer() = default;
	virtual void OnDetach() override;
	virtual void OnAttach() override;
	virtual void OnUpdate(EulerEngine::TimerSystem ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(EulerEngine::Event& e) override;
private:
	EulerEngine::CameraController m_OrthoCameraController;
	EulerEngine::Ref<EulerEngine::Texture2D> m_SpriteSheet;
	EulerEngine::Ref<EulerEngine::EulerMaterial> m_Material;
	EulerEngine::Ref<EulerEngine::EulerShader> m_Shader;
	glm::vec4 m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
};