#pragma once
#include"GutKink.h"
#include"Panels/HierarchyPanel.h"
namespace EulerEngine { 
	class EditorLayer :public EulerLayer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
		virtual void OnDetach() override;
		virtual void OnAttach() override;
		virtual void OnUpdate(TimerSystem ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		void NewScene();
		void OpenScene();
		void SaveSceneAs();
	private:
		CameraController m_CameraController;
		glm::vec4 m_Color = { 0.2f, 0.3f, 0.1f, 1.0f };
		glm::vec3 m_CubePositions[10] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};
		Ref<FrameBuffer> m_FrameBuffer;
		Ref<Scene> m_ActiveScene;
		GameObject m_MainCamera;
		GameObject m_CanvasCamera;
		glm::vec2 m_ViewportSize;
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;
		int m_GizmosType = -1;

		HierarchyPanel m_SceneHierarchyPanel;
	};
}
