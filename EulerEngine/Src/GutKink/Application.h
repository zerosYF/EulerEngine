#pragma once
#include"Core.h"
#include"../Core/Events/Event.h"
#include"../Core/Events/ApplicationEvent.h"
#include"../Core/EulerWindow.h"
#include"../Core/Layer/EulerLayerStack.h"
namespace EulerEngine {
	class KINK_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

		void PushLayer(EulerLayer* layer);
		void PushOverlay(EulerLayer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<EulerWindow> m_Window;
		bool m_Running = true;
		EulerLayerStack m_LayerStack;
	};
	Application* CreateApplication();
}

