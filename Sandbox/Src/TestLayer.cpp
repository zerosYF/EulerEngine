#include"TestLayer.h"
#include<../ImGui/imgui.h>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<chrono>
TestLayer::TestLayer():EulerEngine::EulerLayer("TestLayer"), m_CameraController(EulerEngine::PERSPECTIVE)
{
}
void TestLayer::OnDetach()
{
	EulerEngine::Renderer::ShutDown();
}

void TestLayer::OnAttach()
{
	auto shader = m_ResourceLib.LoadShader("common", "Shaders/Camera/first_test.glsl");
	auto texture2D = m_ResourceLib.LoadTexture2D("texture1", "Assets/mytextures/container2.png");
	auto material = m_ResourceLib.LoadMaterial("first");
	material->SetTexture(texture2D);
	EulerEngine::Renderer::Init();

    EulerEngine::FrameBufferSpecification spec;
    spec.Width = 1280;
    spec.Height = 720;
    m_FrameBuffer = EulerEngine::FrameBuffer::Create(spec);
}

void TestLayer::OnUpdate(EulerEngine::TimerSystem ts)
{
	KINK_PROFILE_FUNCTION();
	{
		KINK_PROFILE_SCOPE("camera_controller");
		m_CameraController.OnUpdate(ts);
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

		for (int i = 0; i < 10; i++) {
			float angle = 20.0f * i;
			auto material = m_ResourceLib.GetMaterial("first");
			material->SetColor(m_Color);
			auto shader = m_ResourceLib.GetShader("common");
			EulerEngine::Renderer::DrawCube(m_CubePositions[i], glm::vec3(angle), glm::vec3(0.5f), material, -1);
		}
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

    ImGui::End();
}

void TestLayer::OnEvent(EulerEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
