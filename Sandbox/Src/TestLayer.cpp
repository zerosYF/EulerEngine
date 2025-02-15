#include"TestLayer.h"
#include<../ImGui/imgui.h>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<chrono>

#define PROFILE_SCOPE(name) Timer<std::function<void(const ProfileResult&)>> timer##__LINE__(name,  [&](ProfileResult profileResult) {m_ProfileResults.push_back(profileResult); })
TestLayer::TestLayer():EulerEngine::EulerLayer("TestLayer")
{
}
void TestLayer::OnDetach()
{
}

void TestLayer::OnAttach()
{
	EulerEngine::Renderer::Init();
}

void TestLayer::OnUpdate(EulerEngine::TimerSystem ts)
{
	KINK_PROFILE_FUNCTION();
	{
		KINK_PROFILE_SCOPE("camera_controller");
		m_CameraController.OnUpdate(ts);
	}

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
			EulerEngine::Renderer::DrawCube(m_CubePositions[i], glm::vec3(angle), glm::vec3(0.5f), m_Color);
		}
		EulerEngine::Renderer::EndScene();
	}
}

void TestLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Clear Color", glm::value_ptr(m_Color));
	ImGui::End();
}

void TestLayer::OnEvent(EulerEngine::Event& e)
{
	m_CameraController.OnEvent(e);
}
