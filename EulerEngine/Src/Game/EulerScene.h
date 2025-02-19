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
	private:
		entt::registry m_Registry;
		friend class GameObject;
	};
}