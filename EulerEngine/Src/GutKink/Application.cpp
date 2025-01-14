#include "gkpch.h"
#include "Application.h"
#include "Core/Log/EulerLog.h"
#include "Core/Events/Event.h"
#include "Core/Input/EulerInput.h"
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_opengl3_loader.h>
#include "Render/Renderer.h"
namespace EulerEngine {
#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<EulerWindow>(EulerWindow::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

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
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(unsigned int)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = "";
		std::string fragmentSrc = "";
		m_Shader.reset(new EulerShader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{
		
	}
	void Application :: Run() {
		while (m_Running) {
			RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1.0f });
			RenderCommand::Clear();

			Renderer::BeginScene();
			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);
			Renderer::EndScene();


			for (EulerLayer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
			m_ImGuiLayer->Begin();
			for (EulerLayer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
			auto [x, y] = InputSystem::GetCursorPosition();
		}
	}
	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.IsHandled()) break;
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
	void Application::PushLayer(EulerLayer* layer) {
		m_LayerStack.PushLayer(layer);
	}
	void Application::PushOverlay(EulerLayer* layer) {
		m_LayerStack.PushOverlay(layer);
	}
	
}
