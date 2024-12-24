#include "gkpch.h"
#include "Application.h"
#include "../Core/Log/EulerLog.h"
#include "../Core/Events/Event.h"
#include "../Core/Input/EulerInput.h"
#include <GLFW/glfw3.h>
namespace EulerEngine {
#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<EulerWindow>  (EulerWindow::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));
		m_ImGuiLayer = std::make_unique<ImGuiLayer>();
		PushOverlay(m_ImGuiLayer.get());
	}

	Application::~Application()
	{
	}
	void Application :: Run() {
		while (m_Running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
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
	Application* CreateApplication()
	{
		return nullptr;
	}
}
