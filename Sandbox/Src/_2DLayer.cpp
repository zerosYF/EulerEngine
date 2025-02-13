#include"gkpch.h"
#include"_2DLayer.h"
#include<../ImGui/imgui.h>

_2DLayer::_2DLayer():EulerEngine::EulerLayer("2DLayer"), m_OrthoCameraController(1280.0f / 768.0f, false)
{

}

void _2DLayer::OnDetach()
{
	EulerEngine::Renderer2D::ShutDown();
}

void _2DLayer::OnAttach()
{
	EulerEngine::Renderer2D::Init();
}

void _2DLayer::OnUpdate(EulerEngine::TimerSystem ts)
{
	m_OrthoCameraController.OnUpdate(ts);

	EulerEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.3f, 1.0f });
	EulerEngine::RenderCommand::Clear();

	EulerEngine::Renderer2D::BeginScene(m_OrthoCameraController.GetCamera());
	EulerEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, m_Color);
	EulerEngine::Renderer2D::EndScene();
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


