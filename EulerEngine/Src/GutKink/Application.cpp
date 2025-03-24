#include"gkpch.h"
#include"Application.h"
#include"Core/Logs/EulerLog.h"
#include"Core/Events/Event.h"
#include"Core/IO/EulerInput.h"
#include<GLFW/glfw3.h>
#include<backends/imgui_impl_opengl3_loader.h>
#include"Render/Renderer/Renderer.h"
#include"Script/ScriptEngine.h"
#include"Core/Global/EulerTimer.h"
namespace EulerEngine {
	Application* Application::s_Instance = nullptr;
	Application::Application(const ApplicationSpecification& spec):m_Specification(spec)
	{
		s_Instance = this;
		m_Window = std::unique_ptr<EulerWindow>(EulerWindow::Create());
		m_Window->SetEventCallback(KINK_BIND_EVENT_FUNC(Application::OnEvent));

		if (!m_Specification.WorkingDir.empty()) {
			std::filesystem::current_path(m_Specification.WorkingDir);
		}

		Renderer::Init();
		ScriptEngine::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		ScriptEngine::ShutDown();
	}
	void Application :: Run() {
		while (m_Running) {
			TimerSystem::Tick();
			ExecuteMainthreadQueue();   
			for (EulerLayer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
			m_ImGuiLayer->Begin();
			for (EulerLayer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			m_Window->OnUpdate();
		}
	}
	void Application::Close() {
		m_Running = false;
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(KINK_BIND_EVENT_FUNC(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.IsHandled()) break;
		}
	}
	void Application::SubmitToMainThread(const std::function<void()>& func)
	{
		std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);
		m_MainThreadQueue.emplace_back(func);
	}
	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
	void Application::ExecuteMainthreadQueue()
	{
		std::scoped_lock<std::mutex> lock(m_MainThreadQueueMutex);
		for (auto& func : m_MainThreadQueue) {
			func();
		}
		m_MainThreadQueue.clear();
	}
	void Application::PushLayer(EulerLayer* layer) {
		m_LayerStack.PushLayer(layer);
	}
	void Application::PushOverlay(EulerLayer* layer) {
		m_LayerStack.PushOverlay(layer);
	}
	
}
