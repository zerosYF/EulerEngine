#pragma once
#include"GutKink.h"
#include"Panels/HierarchyPanel.h"
#include"Panels/AssetBrowserPanel.h"
#include<filesystem>
namespace EulerEngine { 
	class EditorLayer :public EulerLayer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
		virtual void OnDetach() override;
		virtual void OnAttach() override;
		virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
	private:
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

		void OnOverlayRender();

		void NewProject();
		bool OpenProject();
		void OpenProject(const std::filesystem::path& path);
		void SaveProject();

		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveScene();
		void SaveSceneAs();

		void OnSimulationPlay();
		void OnSimulationStop();
		void OnScenePlay();
		void OnSceneSimulate();
		void OnSceneStop();
		void OnScenePause();

		void OnDuplicateGameObject();
		void UI_Toolbar();
	private:
		CameraController m_EditorCameraController;
		glm::vec4 m_Color = { 0.3f, 0.3f, 0.4f, 1.0f };
		glm::vec4 m_PhysicsVisibleColor = { 1.0f, 0.647f, 0.0f, 1.0f };
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
		Ref<Scene> m_EditorScene;
		std::filesystem ::path m_EditingScenePath;

		GameObject m_MainCamera;
		GameObject m_CanvasCamera;

		glm::vec2 m_ViewportSize;
		glm::vec2 m_ViewportBounds[2];
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;
		int m_GizmosType = -1;

		HierarchyPanel m_SceneHierarchyPanel;
		Scope<AssetBrowserPanel> m_AssetBrowserPanel;
		GameObject m_HoveredGameObject;

		enum class SceneState {
			Edit = 0,
			Play = 1,
			Simulate = 2,
		};
		SceneState m_SceneState = SceneState::Edit;

		Ref<Texture2D> m_IconPlay;
		Ref<Texture2D> m_IconStop;
		Ref<Texture2D> m_IconSimulate;
		Ref<Texture2D> m_IconPause;
		Ref<Texture2D> m_IconStep;

		bool m_ShowPhysicsColliders = false;
	};
}
