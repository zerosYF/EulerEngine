#include"TestLayer.h"
#include<../ImGui/imgui.h>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
TestLayer::TestLayer():EulerEngine::EulerLayer("TestLayer"), m_CameraController()
{

}
void TestLayer::OnDetach()
{

}

void TestLayer::OnAttach()
{
	m_VertexArray = EulerEngine::VertexArray::Create();

	EulerEngine::Ref<EulerEngine::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(EulerEngine::VertexBuffer::Create(EulerEngine::CubeVertices, sizeof(EulerEngine::CubeVertices)));

	EulerEngine::BufferLayout layout = {
		{EulerEngine::ShaderDataType::Float3, "aPosition"},
		{EulerEngine::ShaderDataType::Float2, "aTexCoord"},
		{EulerEngine::ShaderDataType::Float3, "aNormal"},
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	auto shader = m_ResourceLib.LoadShader("common", "Shaders/Light/common.glsl");
	auto texture2D = m_ResourceLib.LoadTexture2D("container", "Assets/mytextures/container2.png", EulerEngine::TextureType::DIFFUSE);
	EulerEngine::Ref<EulerEngine::Material> material = EulerEngine::CreateRef<EulerEngine::Material>(shader);
	material->AddTexture("container", texture2D);
	m_ResourceLib.AddMaterial("first", material);

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
		EulerEngine::Renderer::Submit(m_VertexArray, shader, material_ref, model);
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
