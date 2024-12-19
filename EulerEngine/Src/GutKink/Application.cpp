 #include "gkpch.h"
#include "Application.h"
#include "../Core/EulerLog.h"
#include "../Core/Events/Event.h"
namespace EulerEngine {
#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application()
	{
		m_Window = std::unique_ptr<EulerWindow>  (EulerWindow::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));
	}

	Application::~Application()
	{
	}
	void Application :: Run() {
		while (m_Running) {
			m_Window->OnUpdate();
			for (EulerLayer* layer:m_LayerStack) {
				layer->OnUpdate();
			}
		}
	}
	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));
		KINK_CORE_TRACE("dispatch event {0}", e.ToString());

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
