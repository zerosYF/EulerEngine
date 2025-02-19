#pragma once
#include"entt.hpp"
#include"Core/EulerTimer.h"
namespace EulerEngine {
	class Scene {
	public:
		Scene();
		~Scene();
		entt::entity CreateEntity();
		entt::registry& GetRegistry() { return m_Registry; }
		void OnUpdate(TimerSystem ts);
	private:
		entt::registry m_Registry;
	};
}