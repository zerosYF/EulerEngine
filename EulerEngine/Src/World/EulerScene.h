#pragma once
#include"entt.hpp"
#include"Core/EulerTimer.h"
#include"Core/EulerUUID.h"
#include"Render/Camera/EulerCamera.h"
#include"world.h"
#include"body.h"
#include"shape.h"
#include"box2d/box2d.h"
class b2World;
namespace EulerEngine {
	class GameObject;
	class Scene {
	public:
		Scene();
		~Scene();
		static Ref<Scene> Copy(Ref<Scene> scene);

		GameObject CreateObject(const std::string& name="GameObject");
		GameObject CreateObject(EulerUUID uuid, const std::string& name="GameObject");
		void DuplicateObject(GameObject obj);
		void DestroyObject(GameObject& obj);

		void OnRuntimeStart();
		void OnRuntimeStop();
		void OnSimulationStart();
		void OnSimulationStop();

		void OnUpdateEditor(TimerSystem ts, EulerCamera& editorCamera);
		void OnUpdateRuntime(TimerSystem ts);
		void OnUpdateSimulation(TimerSystem ts, EulerCamera& editorCamera);

		void OnViewportResize(int width, int height);
		GameObject GetGameObject(unsigned int UUID);
		GameObject GetPrimaryCamera();

		template<typename... Components>
		auto GetAllEntitiesWith() {
			return m_Registry.view<Components...>();
		}

	private:
		template<typename T>
		void OnComponentAdded(GameObject obj, T& component);
		void OnPhysics2DStart(); 
		void OnPhysics2DStop();
		void OnRenderScene(EulerCamera& camera);
		void OnPhysics2DUpdate(TimerSystem ts);
	private:
		entt::registry m_Registry;
		unsigned int m_ViewportWidth = 1200;
		unsigned int m_ViewportHeight = 720;

		b2WorldId m_PhysicsWorld;

		friend class GameObject;
		friend class SceneSerializer;
		friend class HierarchyPanel;
	};

}