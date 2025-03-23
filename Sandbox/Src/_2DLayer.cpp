#include"gkpch.h"
#include"_2DLayer.h"
#include<../ImGui/imgui.h>

_2DLayer::_2DLayer():EulerEngine::EulerLayer("2DLayer"), m_OrthoCameraController()
{
	m_OrthoCameraController.GetCamera().SetCameraType(EulerEngine::ORTHOGRAPHIC);
}

void _2DLayer::OnDetach()
{
	EulerEngine::Renderer::ShutDown();
}

void _2DLayer::OnAttach()
{
	EulerEngine::Renderer::Init();
}

void _2DLayer::OnUpdate(EulerEngine::TimerSystem ts)
{
	m_OrthoCameraController.OnUpdate(ts);

	EulerEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.3f, 1.0f });
	EulerEngine::RenderCommand::Clear();

	EulerEngine::Renderer::BeginScene(m_OrthoCameraController.GetCamera());
	EulerEngine::Renderer::DrawQuad({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, { 1.0f, 1.0f, 1.0f }, m_Material, -1);
	EulerEngine::Renderer::EndScene();
}

void _2DLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Clear Color", glm::value_ptr(m_Color));
	ImGui::End();
}

void _2DLayer::OnEvent(EulerEngine::Event& e)
{
	m_OrthoCameraController.OnEvent(e);
}


