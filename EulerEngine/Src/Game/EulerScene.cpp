#include"gkpch.h"
#include"EulerScene.h"
#include"Component/TransformComponent.h"
#include"Component/RendererComponent.h"
#include"Component/TagComponent.h"
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
	GameObject Scene::CreateObject(const std::string& name)
	{
		GameObject go = { m_Registry.create(), this };
		go.AddComponent<TransformComponent>();
		go.AddComponent<TagComponent>(name);
		return go;
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