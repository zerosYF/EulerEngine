#include "gkpch.h"
#include"EulerObject.h"
namespace EulerEngine {
	GameObject::GameObject(entt::entity entity, Scene* scene) 
		:m_Entity(entity), m_Scene(scene) {

	}
	
}