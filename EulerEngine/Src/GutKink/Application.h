#pragma once
#include"Core.h"
#include"Core/Events/Event.h"
#include"Core/Events/ApplicationEvent.h"
#include"Core/EulerWindow.h"
#include"ImGui/ImGuiLayer.h"
#include"Core/Layer/EulerLayerStack.h"
#include"Render/EulerShader.h"
#include"Render/EulerBuffer.h"
#include"Render/VertexArray.h"
#include"Core/EulerTimer.h"
namespace EulerEngine {
	struct ApplicationCommandLineArgs {
		int Count = 0;
		char** args = nullptr;
		const char* operator[](int index) const{
			return args[index];
		}
	};
	struct ApplicationSpecification {
		std::string Name;
		std::string WorkingDir;
		ApplicationCommandLineArgs CmdArgs;
	};
	class KINK_API Application
	{
	public:
		Application(const ApplicationSpecification& spec);
		virtual ~Application();
		void Run();
		void Close();
		void OnEvent(Event& e);

		void PushLayer(EulerLayer* layer);
		void PushOverlay(EulerLayer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline EulerWindow& GetWindow() { return *m_Window; }
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		ApplicationSpecification m_Specification;
		std::unique_ptr<EulerWindow> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		EulerLayerStack m_LayerStack;
		static Application* s_Instance;
		TimerSystem m_Timer;
	};
	Application* CreateApplication(ApplicationCommandLineArgs args);
}

