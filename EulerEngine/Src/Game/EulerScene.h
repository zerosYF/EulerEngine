#pragma once
#include"entt.hpp"
#include"Core/EulerTimer.h"
namespace EulerEngine {
	class GameObject;
	class Scene {
	public:
		Scene();
		~Scene();
		GameObject CreateObject(const std::string& name="GameObject");
		void OnUpdate(TimerSystem ts);
		void OnViewportResize(int width, int height);
	private:
		entt::registry m_Registry;
		unsigned int m_ViewportWidth = 0.0f;
		unsigned int m_ViewportHeight = 0.0f;
		friend class GameObject;
	};
}