#pragma once
#include"entt/entt.hpp"
#include"Core/Global/EulerTimer.h"
#include"Core/Global/EulerUUID.h"
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
		void DestroyObject(GameObject obj);

		void OnRuntimeStart();
		void OnRuntimeStop();
		void OnSimulationStart();
		void OnSimulationStop();

		void OnUpdateEditor(EulerCamera& editorCamera);
		void OnUpdateRuntime();
		void OnUpdateSimulation(EulerCamera& editorCamera);

		void OnViewportResize(int width, int height);
		GameObject GetGameObject(uint64_t UUID);
		GameObject GetGameObjectByName(std::string name);
		GameObject GetPrimaryCamera();

		bool IsRunning() const { return m_IsRunning; }
		bool IsPaused() const { return m_IsPaused; }
		void Pause(bool pause) { m_IsPaused = pause; }
		void Step(int frame = 1);

		template<typename... Components>
		auto GetAllEntitiesWith() {
			return m_Registry.view<Components...>();
		}

	private:
		template<typename T>
		void OnComponentAdded(GameObject obj, T& component);
		void RenderScene(EulerCamera& camera);

		void OnPhysics2DStart(); 
		void OnPhysics2DStop();
		void OnPhysics2DUpdate();

		void OnPhysicsStart();
		void OnPhysicsStop();
		void OnPhysicsUpdate();

		void OnNativeScriptStart();
		void OnNativeScriptStop();
		void OnNativeScriptUpdate();

		void OnCSharpScriptStart();
		void OnCSharpScriptStop();
		void OnCSharpScriptUpdate();
	private:
		entt::registry m_Registry;
		unsigned int m_ViewportWidth = 1200;
		unsigned int m_ViewportHeight = 720;

		b2WorldId m_PhysicsWorld;
		std::unordered_map<EulerUUID, entt::entity> m_EntityMap;

		bool m_IsRunning = false;
		bool m_IsPaused = false;
		int m_StepFrame = 0;
		friend class GameObject;
		friend class SceneSerializer;
		friend class HierarchyPanel;
	};

}