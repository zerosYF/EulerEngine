#include"gkpch.h"
#include<GutKink.h>
using namespace EulerEngine;
class ExampleLayer : public EulerEngine::EulerLayer {
public:
	ExampleLayer()
		: m_Camera()
	{
		m_VertexArray.reset(VertexArray::Create());

		float vertices[9]{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3]{ 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = "";
		std::string fragmentSrc = "";
		m_Shader.reset(new EulerShader(vertexSrc, fragmentSrc));
	}
	void OnUpdate(TimerSystem timer) override{
		if (InputSystem::IsKeyDown(KINK_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraSpeed * timer.GetDeltaTime();
		}
		RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		RenderCommand::Clear();

		Renderer::BeginScene(m_Camera);

		Renderer::Submit(m_VertexArray, m_Shader);
		Renderer::EndScene();
	}
	void OnEvent(EulerEngine::Event& event) override {
		
	}
private:
	std::shared_ptr<VertexArray> m_VertexArray;
	std::shared_ptr<EulerShader> m_Shader;
	Camera m_Camera;
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraSpeed = 5.0f;
};
class Sandbox : public EulerEngine::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {
	}
};
EulerEngine::Application* EulerEngine::CreateApplication() {
	return new Sandbox();
}