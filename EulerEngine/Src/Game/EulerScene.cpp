#include"gkpch.h"
#include"EulerScene.h"
#include"Component/Component.h"
#include"Render/Renderer.h"
#include"EulerObject.h"
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
		Ref<EulerCamera> mainCamera = nullptr;
		auto group = m_Registry.group<CameraComponent>(entt::get<TransformComponent>);
		for (auto entity : group) {
			auto& [transform, camera] = group.get<TransformComponent, CameraComponent>(entity);
			if (camera.isPrimary) {
				mainCamera = camera.Camera;
				mainCamera->SetPosition(transform.Position);
				mainCamera->SetRotation(transform.Rotation);
				break;
			}
		}
		if (mainCamera) {
			Renderer::BeginScene(mainCamera);
			auto group = m_Registry.group<TransformComponent>(entt::get<RendererComponent>);
			for (auto entity : group) {
				auto& [transform, mesh] = group.get<TransformComponent, RendererComponent>(entity);
				Renderer::DrawCube(transform.Position, transform.Rotation, transform.Scale, mesh.Color);
			}
			Renderer::EndScene();
		}
	}
}