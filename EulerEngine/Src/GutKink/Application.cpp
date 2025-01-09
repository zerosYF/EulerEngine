#include "gkpch.h"
#include "Application.h"
#include "../Core/Log/EulerLog.h"
#include "../Core/Events/Event.h"
#include "../Core/Input/EulerInput.h"
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_opengl3_loader.h>
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

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[9]{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		unsigned int indices[3]{ 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(unsigned int)));

		std::string vertexSrc = "";
		std::string fragmentSrc = "";
		m_Shader.reset(new EulerShader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{
		
	}
	void Application :: Run() {
		while (m_Running) {
			glClearColor(0.1f, 0, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);


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
