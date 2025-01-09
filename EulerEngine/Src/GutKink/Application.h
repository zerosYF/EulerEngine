#pragma once
#include"Core.h"
#include"../Core/Events/Event.h"
#include"../Core/Events/ApplicationEvent.h"
#include"../Core/EulerWindow.h"
#include"../ImGui/ImGuiLayer.h"
#include"../Core/Layer/EulerLayerStack.h"
#include"Render/EulerShader.h"
#include"Render/EulerBuffer.h"
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

		inline static Application& Get() { return *s_Instance; }
		inline EulerWindow& GetWIndow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<EulerWindow> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		EulerLayerStack m_LayerStack;
		static Application* s_Instance;

		unsigned int m_VertexArray;
		std::unique_ptr<EulerShader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};
	Application* CreateApplication();
}

