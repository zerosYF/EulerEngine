#include"TestLayer.h"
#include<../ImGui/imgui.h>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<chrono>
TestLayer::TestLayer():EulerEngine::EulerLayer("TestLayer"), m_CameraController()
{
}
void TestLayer::OnDetach()
{
	EulerEngine::Renderer::ShutDown();
}

void TestLayer::OnAttach()
{
	EulerEngine::Renderer::Init();

    EulerEngine::FrameBufferSpecification spec;
    spec.Width = 1280;
    spec.Height = 720;
    m_FrameBuffer = EulerEngine::FrameBuffer::Create(spec);
}

void TestLayer::OnUpdate()
{
	KINK_PROFILE_FUNCTION();
	{
		KINK_PROFILE_SCOPE("camera_controller");
		m_CameraController.OnUpdate();
	}
	EulerEngine::Renderer::ResetStatistic();
	{
		KINK_PROFILE_SCOPE("renderer_prep");
		EulerEngine::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		EulerEngine::RenderCommand::Clear();
	}

	{
		KINK_PROFILE_SCOPE("renderer_draw");
		EulerEngine::Renderer::BeginScene(m_CameraController.GetCamera());
		EulerEngine::Renderer::EndScene();
	}
}

void TestLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Clear Color", glm::value_ptr(m_Color));
    ImGui::Text("Renderer Info:");
    ImGui::Text("Draw Calls: %d", EulerEngine::Renderer::GetStats().DrawCalls);
    ImGui::Text("Cubes: %d", EulerEngine::Renderer::GetStats().CubeCount);
    ImGui::Text("Vertices: %d", EulerEngine::Renderer::GetStats().GetTotalVertexCount());
    ImGui::Text("Indices: %d", EulerEngine::Renderer::GetStats().GetTotalIndexCount());

    ImGui::End();
}

void TestLayer::OnEvent(EulerEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
