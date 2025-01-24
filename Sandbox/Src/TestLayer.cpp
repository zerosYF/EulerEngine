#include"TestLayer.h"
#include<../ImGui/imgui.h>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
TestLayer::TestLayer():EulerEngine::EulerLayer("TestLayer"), m_Camera()
{

}
void TestLayer::OnDetach()
{

}

void TestLayer::OnAttach()
{
	EulerEngine::Renderer::Init();
	m_VertexArray = EulerEngine::VertexArray::Create();

	float vertices[9]{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	EulerEngine::Ref<EulerEngine::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(EulerEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

	EulerEngine::BufferLayout layout = {
		{EulerEngine::ShaderDataType::Float3, "a_Position"},
		{EulerEngine::ShaderDataType::Float2, "a_TexCoord"},
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	unsigned int indices[3]{ 0, 1, 2 };
	EulerEngine::Ref<EulerEngine::IndexBuffer> indexBuffer;
	indexBuffer.reset(EulerEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	std::string vertexSrc = "";
	std::string fragmentSrc = "";
	m_Shader = EulerEngine::EulerShader::Create("first", vertexSrc, fragmentSrc);
	m_ResourceLib.AddShader(m_Shader);
	m_Texture2D = EulerEngine::Texture2D::Create("", EulerEngine::TextureType::DIFFUSE);
}

void TestLayer::OnUpdate(EulerEngine::TimerSystem ts)
{
	m_Camera.OnUpdate(ts);

	if (EulerEngine::InputSystem::IsKeyDown(KINK_KEY_LEFT)) {
		m_CameraPosition.x -= m_CameraSpeed * ts.GetDeltaTime();
	}
	EulerEngine::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
	EulerEngine::RenderCommand::Clear();

	EulerEngine::Renderer::BeginScene(m_Camera);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_CameraPosition);
	EulerEngine::Ref<EulerEngine::Material> material_ref = EulerEngine::CreateRef<EulerEngine::Material>(m_Shader);
	std::vector<unsigned int> indices;
	EulerEngine::Ref<EulerEngine::Mesh> mesh = EulerEngine::CreateRef<EulerEngine::Mesh>(EulerEngine::vertices, indices);
	m_Texture2D->Bind();

	EulerEngine::Renderer::Submit(m_VertexArray, m_Shader, material_ref, transform);
	EulerEngine::Renderer::EndScene();
}

void TestLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	glm::vec4 color = glm::vec4(1.0f);
	ImGui::ColorEdit4("Clear Color", glm::value_ptr(color));
	ImGui::End();
}

void TestLayer::OnEvent(EulerEngine::Event& e)
{
	m_Camera.OnEvent(e);
}
