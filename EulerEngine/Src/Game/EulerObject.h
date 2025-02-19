#pragma once
#include<tchar.h>
#include<vector>
#include<memory>
#include<atomic>
#include<iostream>
#include"Component/ComponentBase.h"
#include"entt.hpp"
#include"GutKink/Core.h"
#include"EulerScene.h"
namespace EulerEngine {
	class GameObject{
	public:
		GameObject(entt::entity entity, Scene* scene);
		GameObject(const GameObject& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			KINK_CORE_ASSERT(HasComponent<T>() == false, "Component already exists on GameObject");
			return m_Scene->m_Registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
		}
		template<typename T>
		T& GetComponent() {
			KINK_CORE_ASSERT(HasComponent<T>(), "Component does not exist on GameObject");
			return m_Scene->m_Registry.get<T>(m_Entity);
		}

		template<typename T>
		bool HasComponent(){
			return m_Scene->m_Registry.try_get<T>(m_Entity)!= nullptr;
		}
		template<typename T>
		void RemoveComponent() {
			KINK_CORE_ASSERT(HasComponent<T>(), "Component does not exist on GameObject");
			m_Scene->m_Registry.remove<T>(m_Entity);
		}
		operator bool() const { return (unsigned int)m_Entity != 0; }
	private:
		entt::entity m_Entity{0};
		Scene* m_Scene = nullptr;
	};
}