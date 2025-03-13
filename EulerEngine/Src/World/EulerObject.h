#pragma once
#include"Component/Component.h"
#include"entt/entt.hpp"
#include"GutKink/Core.h"
#include"EulerScene.h"
#include"Core/EulerUUID.h"
namespace EulerEngine {
	class GameObject{
	public:
		GameObject() = default;
		GameObject(entt::entity entity, Scene* scene);
		GameObject(const GameObject& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			KINK_CORE_ASSERT(HasComponent<T>() == false, "Component already exists on GameObject");
			T& component = m_Scene->m_Registry.emplace<T>(m_Entity, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}
		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args) {
			T& component = m_Scene->m_Registry.emplace_or_replace<T>(m_Entity, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
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
		operator bool() const { return m_Entity != entt::null; }
		operator unsigned int() const { return (unsigned int)m_Entity; }
		operator entt::entity() const { return m_Entity; }
		bool operator ==(const GameObject& other) const { return m_Entity == other.m_Entity && m_Scene == other.m_Scene; }
		EulerUUID GetUUID() { return GetComponent<IDCom>().ID; }
		std::string GetName() { return GetComponent<Profile>().Tag; }

	private:
		entt::entity m_Entity{entt::null};
		Scene* m_Scene = nullptr;
	};
}