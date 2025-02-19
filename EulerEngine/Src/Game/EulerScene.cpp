#include"gkpch.h"
#include"EulerScene.h"
#include"Component/TransformComponent.h"
#include"Component/RendererComponent.h"
#include"Render/Renderer.h"
namespace EulerEngine {
	Scene::Scene()
	{
		entt::entity entity = m_Registry.create();
		m_Registry.emplace<TransformComponent>(entity);
	}
	Scene::~Scene()
	{
	}
	entt::entity Scene::CreateEntity()
	{
		return m_Registry.create();
	}
	void Scene::OnUpdate(TimerSystem ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<RendererComponent>);
		for (auto entity : group) {
			auto& [transform, mesh] = group.get<TransformComponent, RendererComponent>(entity);
			Renderer::DrawCube(transform.Position, transform.Rotation, transform.Scale,  mesh.Color);
		}
	}
}