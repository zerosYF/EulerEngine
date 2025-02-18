#pragma once
#include"entt.hpp"
#include"Core/EulerTimer.h"
namespace EulerEngine {
	class Scene {
	public:
		Scene();
		~Scene();
		void OnUpdate(TimerSystem ts);
	private:
		entt::registry m_Registry;
	};
}