#include "gkpch.h"
#include "Application.h"
#include "Core/Logs/EulerLog.h"
#include "Core/Events/Event.h"
#include "Core/Input/EulerInput.h"
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_opengl3_loader.h>
#include "Render/Renderer.h"
namespace EulerEngine {
	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		s_Instance = this;
		m_Window = std::unique_ptr<EulerWindow>(EulerWindow::Create());
		m_Window->SetEventCallback(KINK_BIND_EVENT_FUNC(Application::OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_Timer = TimerSystem();
	}

	Application::~Application()
	{
		
	}
	void Application :: Run() {
		while (m_Running) {
			m_Timer.Tick();
			for (EulerLayer* layer : m_LayerStack) {
				layer->OnUpdate(m_Timer);
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
		dispatcher.Dispatch<WindowCloseEvent>(KINK_BIND_EVENT_FUNC(Application::OnWindowClose));

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
