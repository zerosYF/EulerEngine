#pragma once
#include"entt.hpp"
#include"Core/EulerTimer.h"
#include"Render/Camera/EulerCamera.h"
namespace EulerEngine {
	class GameObject;
	class Scene {
	public:
		Scene();
		~Scene();
		GameObject CreateObject(const std::string& name="GameObject");
		GameObject CreateObject(unsigned int UUID, const std::string& name="GameObject");
		void DestroyObject(GameObject& obj);
		void OnUpdateEditor(TimerSystem ts, Ref<EulerCamera> editorCamera);
		void OnUpdateRuntime(TimerSystem ts);
		void OnViewportResize(int width, int height);
		GameObject GetGameObject(unsigned int UUID);
		GameObject GetPrimaryCamera();
	private:
		template<typename T>
		void OnComponentAdded(GameObject obj, T& component);
	private:
		entt::registry m_Registry;
		unsigned int m_ViewportWidth = 1200;
		unsigned int m_ViewportHeight = 720;
		friend class GameObject;
		friend class SceneSerializer;
		friend class HierarchyPanel;
	};

}