#pragma once
#include"Core.h"
#include"../Core/Events/Event.h"
#include"../Core/Events/ApplicationEvent.h"
#include"../Core/EulerWindow.h"
namespace EulerEngine {
	class KINK_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<EulerWindow> m_Window;
		bool m_Running = true;
	};
	Application* CreateApplication();
}

