#include"gkpch.h"
#include"EulerScene.h"
#include"Component/Component.h"
#include"Render/Renderer/Renderer.h"
#include"EulerObject.h"
#include"EulerBehaviour.h"
#include"Resource/ResourceLibrary.h"
namespace EulerEngine {
	Scene::Scene()
	{
	}
	Scene::~Scene()
	{
	}
	GameObject Scene::CreateObject(const std::string& name)
	{
		GameObject go = { m_Registry.create(), this };
		go.AddComponent<Transform>();
		go.AddComponent<Profile>(name);
		return go;
	}
	void Scene::DestroyObject(GameObject& obj)
	{
		m_Registry.destroy(obj);
	}
	void Scene::OnUpdate(TimerSystem ts)
	{
		m_Registry.view<NativeScript>().each([=](auto entity, auto& nsc) {
			if (nsc.Instance == nullptr) {
				nsc.Instance = nsc.InstantiateScript();
				nsc.Instance->m_gameObject = GameObject{entity, this};
				nsc.Instance->OnCreate();
			}
			nsc.Instance->OnUpdate(ts);

		});

		Ref<EulerCamera> mainCamera = nullptr;
		auto group = m_Registry.group<Camera>(entt::get<Transform>);
		for (auto entity : group) {
			auto& [transform, camera] = group.get<Transform, Camera>(entity);
			if (camera.isPrimary) {
				mainCamera = camera.RendererCamera;
				mainCamera->SetPosition(transform.Position);
				mainCamera->SetRotation(transform.Rotation);
				break;
			}
		}
		if (mainCamera) {
			Renderer::BeginScene(mainCamera);
			auto group = m_Registry.group<Transform>(entt::get<MeshRenderer>);
			for (auto entity : group) {
				auto& [transform, mesh] = group.get<Transform, MeshRenderer>(entity);
				Renderer::DrawCube(transform.Position, transform.Rotation, transform.Scale, mesh.Material);
			}
			Renderer::EndScene();
		}
	}
	void Scene::OnViewportResize(int width, int height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;
		auto view = m_Registry.view<Camera>();
		for (auto entity: view) {
			auto& camera_com = view.get<Camera>(entity);
			if (!camera_com.isFixedAspectRatio) {
				camera_com.RendererCamera->SetAspectRatio(float(m_ViewportWidth) / float(m_ViewportHeight));
			}
		}
	}

	template<typename T>
	void Scene::OnComponentAdded(GameObject obj, T& component) {
		static_assert(false);
	}

	/// <summary>
	/// template specialization for Components
	/// </summary>
	/// <param name="obj"></param>
	/// <param name="component"></param>
	template<>
	void Scene::OnComponentAdded<Profile>(GameObject obj, Profile& component) {
	}
	template<>
	void Scene::OnComponentAdded<Transform>(GameObject obj, Transform& component) {
		
	}
	template<>
	void Scene::OnComponentAdded<Camera>(GameObject obj, Camera& component) {
		//KINK_CORE_ERROR("viewport_size:{0}, {1}", m_ViewportWidth, m_ViewportHeight);
		component.RendererCamera->SetAspectRatio((float)m_ViewportWidth / (float)m_ViewportHeight);
	}
	template<>
	void Scene::OnComponentAdded<MeshRenderer>(GameObject obj, MeshRenderer& component) {
		//temp;
		auto shader = ResourceLibrary::GetResourceLibrary()->GetShader("common");
		auto texture2D = ResourceLibrary::GetResourceLibrary()->GetTexture2D("cube_texture");
		auto material = EulerMaterial::Create();
		material->SetShader(shader);
		material->SetColor(glm::vec4(1.0f));
		material->SetTexture(texture2D);
		component.Material = material;
	}
	template<>
	void Scene::OnComponentAdded<NativeScript>(GameObject obj, NativeScript& component) {
		
	}
}