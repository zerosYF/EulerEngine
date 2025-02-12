#include"TestLayer.h"
#include<../ImGui/imgui.h>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
TestLayer::TestLayer():EulerEngine::EulerLayer("TestLayer")
{
}
void TestLayer::OnDetach()
{
}

void TestLayer::OnAttach()
{
	EulerEngine::Renderer::Init();

	m_VertexArray = EulerEngine::VertexArray::Create();

	EulerEngine::Ref<EulerEngine::VertexBuffer> vertexBuffer
		= EulerEngine::VertexBuffer::Create(EulerEngine::CubeVerticesWithoutNormal, sizeof(EulerEngine::CubeVerticesWithoutNormal));

	EulerEngine::BufferLayout layout = {
		{EulerEngine::ShaderDataType::Float3, "aPosition"},
		{EulerEngine::ShaderDataType::Float2, "aTexCoord"},
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	m_ResourceLib.LoadShader("common", "Shaders/Camera/first_test.glsl");
	auto texture2D = m_ResourceLib.LoadTexture2D("texture1", "Assets/mytextures/container2.png");
	auto material = m_ResourceLib.LoadMaterial("first");
    material->AddTexture("container", texture2D);

}

void TestLayer::OnUpdate(EulerEngine::TimerSystem ts)
{
	m_CameraController.OnUpdate(ts);

	EulerEngine::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
	EulerEngine::RenderCommand::Clear();


	EulerEngine::Renderer::BeginScene(m_CameraController.GetCamera());

	auto shader = m_ResourceLib.GetShader("common");
	auto material_ref = m_ResourceLib.GetMaterial("first");
	material_ref->SetColor(m_Color);
	for (int i = 0; i < 10; i++) {
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_CubePositions[i]);
		float angle = 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		EulerEngine::Renderer::Submit(m_VertexArray, shader, material_ref, model, 36);
	}
	EulerEngine::Renderer::EndScene();
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
