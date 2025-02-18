#include"gkpch.h"
#include"EulerScene.h"
#include"Component/TransformComponent.h"
namespace EulerEngine {
	Scene::Scene()
	{
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity);
	}
	Scene::~Scene()
	{
	}
	void Scene::OnUpdate(TimerSystem ts)
	{

	}
}