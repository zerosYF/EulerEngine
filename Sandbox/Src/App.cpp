#include"gkpch.h"
#include<GutKink.h>
#include<../ImGui/imgui.h>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtc/matrix_transform.hpp>
using namespace EulerEngine;
class ExampleLayer : public EulerEngine::EulerLayer {
public:
	ExampleLayer()
		: m_Camera()
	{
		Renderer::Init();
		m_VertexArray = VertexArray::Create();

		float vertices[9]{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		Ref<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3]{ 0, 1, 2 };
		Ref<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = "";
		std::string fragmentSrc = "";
		m_Shader = EulerShader::Create(vertexSrc, fragmentSrc);
		m_Texture = Texture2D::Create("", TextureType::DIFFUSE);
	}
	void OnUpdate(TimerSystem timer) override{
		if (InputSystem::IsKeyDown(KINK_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraSpeed * timer.GetDeltaTime();
		}
		RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
		RenderCommand::Clear();

		Renderer::BeginScene(m_Camera);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_CameraPosition);
		Ref<Material> material_ref = CreateRef<Material>(m_Shader);
		std::vector<unsigned int> indices;
		Ref<Mesh> mesh = CreateRef<Mesh>(vertices, indices);
		m_Texture->Bind();

		Renderer::Submit(m_VertexArray, m_Shader, material_ref, transform);
		Renderer::EndScene();
	}
	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		glm::vec4 color = glm::vec4(1.0f);
		ImGui::ColorEdit4("Clear Color", glm::value_ptr(color)); 
		ImGui::SliderFloat("Camera Speed", &m_CameraSpeed, 0.0f, 100.0f);
		ImGui::End();
	}
	void OnEvent(EulerEngine::Event& event) override {
		
	}
private:
	Ref<VertexArray> m_VertexArray;
	Ref<EulerShader> m_Shader;
	Ref<Texture2D> m_Texture;
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