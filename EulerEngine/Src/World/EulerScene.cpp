#include"gkpch.h"
#include"EulerScene.h"
#include"Component/Component.h"
#include"Render/Renderer/Renderer.h"
#include"EulerObject.h"
#include"EulerBehaviour.h"
#include"Resource/ResourceLibrary.h"
namespace EulerEngine {
	static b2BodyType KinkRigidbody2DTypeToBox2DType(Rigidbody2D::BodyType type)
	{
		switch (type)
		{
		case Rigidbody2D::BodyType::Static:
			return b2_staticBody;
		case Rigidbody2D::BodyType::Dynamic:
			return b2_dynamicBody;
		case Rigidbody2D::BodyType::Kinematic:
			return b2_kinematicBody;
		default:
			return b2_staticBody;
		}
	}

	Scene::Scene()
	{
	}
	Scene::~Scene()
	{
	}

	template<typename Component>
	static void CopyComponent(entt::registry& dst, entt::registry& src, const std::unordered_map<EulerUUID, entt::entity> entityMap) {
		auto view = src.view<Component>();
		for (auto e : view) {
			EulerUUID id = src.get<IDCom>(e).ID;
			KINK_CORE_INFO("Copying Component");
			entt::entity dstEntity = entityMap.at(id);
			auto& component = src.get<Component>(e);
			dst.emplace_or_replace<Component>(dstEntity, component);
		}
	}
	Ref<Scene> Scene::Copy(Ref<Scene> scene)
	{
		Ref<Scene> newScene = CreateRef<Scene>();
		newScene->m_ViewportWidth = scene->m_ViewportWidth;
		newScene->m_ViewportHeight = scene->m_ViewportHeight;
		
		std::unordered_map<EulerUUID, entt::entity> entityMap;

		auto& srcregistry = scene->m_Registry;
		auto& dstRegistry = newScene->m_Registry;
		auto idView = srcregistry.view<IDCom>();
		for (auto e : idView) {
			EulerUUID id = srcregistry.get<IDCom>(e).ID;
			const auto& name = srcregistry.get<Profile>(e).Tag;
			//KINK_CORE_INFO("Copying Entity:{0}", name);
			GameObject obj = newScene ->CreateObject(id, name);
			entityMap[id] = (entt::entity)obj;
		}
		CopyComponent<Transform>(dstRegistry, srcregistry, entityMap);
		CopyComponent<BoxCollider2D>(dstRegistry, srcregistry, entityMap);
		CopyComponent<Rigidbody2D>(dstRegistry, srcregistry, entityMap);
		CopyComponent<SpriteRenderer>(dstRegistry, srcregistry, entityMap);
		CopyComponent<MeshRenderer>(dstRegistry, srcregistry, entityMap);
		CopyComponent<NativeScript>(dstRegistry, srcregistry, entityMap);
		CopyComponent<Camera>(dstRegistry, srcregistry, entityMap);
		return newScene;
	}
	GameObject Scene::CreateObject(const std::string& name)
	{
		return CreateObject(EulerUUID(), name);
	}
	GameObject Scene::CreateObject(EulerUUID uuid, const std::string& name)
	{
		GameObject go = { m_Registry.create(), this };
		go.AddComponent<IDCom>(uuid);
		go.AddComponent<Transform>();
		go.AddComponent<Profile>(name);
		return go;
	}
	void Scene::DestroyObject(GameObject& obj)
	{
		KINK_CORE_ERROR("Destroy OBJ:{0}", (unsigned int)obj);
		m_Registry.destroy(obj);
	}
	void Scene::OnRuntimeStart()
	{
		b2Vec2 gravity = b2Vec2({0.0f, -9.81f});
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = gravity;
		m_PhysicsWorld = b2CreateWorld(&worldDef);
		auto view = m_Registry.view<Rigidbody2D>();
		for (auto e: view) {
			GameObject obj = { e, this };
			auto& transform = obj.GetComponent<Transform>();
			auto& rb2d = obj.GetComponent<Rigidbody2D>();
			b2BodyDef bodyDef = b2DefaultBodyDef();
			bodyDef.type = KinkRigidbody2DTypeToBox2DType(rb2d.Type);
			bodyDef.position = b2Vec2({ transform.Position.x, transform.Position.y });
			bodyDef.rotation = b2MakeRot(transform.Rotation.z);
			bodyDef.fixedRotation = rb2d.FixedRotation;
			bodyDef.angularDamping = rb2d.AngularDamping;
			bodyDef.linearDamping = rb2d.LinearDamping;
			b2BodyId body = b2CreateBody(m_PhysicsWorld, &bodyDef);
			rb2d.RuntimeBody = body;
			if (obj.HasComponent<BoxCollider2D>()) {
				auto& box2d = obj.GetComponent<BoxCollider2D>();
				b2Polygon polygon = b2MakeBox(box2d.Size.x * transform.Scale.x, box2d.Size.y * transform.Scale.y);
				b2ShapeDef shapeDef = b2DefaultShapeDef();
				b2ShapeId shape = b2CreatePolygonShape(body, &shapeDef, &polygon);

				shapeDef.density = box2d.Density;
				shapeDef.friction = box2d.Friction;
				shapeDef.restitution = box2d.Restitution;
				box2d.ShapeId = shape;
			}
		}
	}
	void Scene::OnRuntimeStop()
	{
		b2DestroyWorld(m_PhysicsWorld);
	}
	void Scene::OnUpdateRuntime(TimerSystem ts)
	{
		m_Registry.view<NativeScript>().each([=](auto entity, auto& nsc) {
			if (nsc.Instance == nullptr) {
				nsc.Instance = nsc.InstantiateScript();
				nsc.Instance->m_gameObject = GameObject{entity, this};
				nsc.Instance->OnCreate();
			}
			nsc.Instance->OnUpdate(ts);

		});

		{
			const int subSteps = 4;
			b2World_Step(m_PhysicsWorld, ts.GetDeltaTime(), subSteps);
			auto view = m_Registry.view<Rigidbody2D>();
			for (auto e : view) {
				GameObject obj = { e, this };
				auto& transform = obj.GetComponent<Transform>();
				auto& rb2d = obj.GetComponent<Rigidbody2D>();
				b2BodyId runtime_body = rb2d.RuntimeBody;
				const auto& position = b2Body_GetPosition(runtime_body);
				transform.Position = glm::vec3(position.x, position.y, transform.Position.z);
				const auto& rotation = b2Body_GetRotation(runtime_body);
				transform.Rotation = glm::vec3(transform.Rotation.x, transform.Rotation.y, b2Rot_GetAngle(rotation));
				KINK_CORE_INFO("pos:{0}, {1}, {2}", transform.Position.x, transform.Position.y, transform.Position.z);
			}
		}

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
			/*auto group = m_Registry.group<Transform>(entt::get<MeshRenderer>);
			for (auto entity : group) {
				auto& [transform, mesh] = group.get<Transform, MeshRenderer>(entity);
				Renderer::DrawCube(transform.Position, transform.Rotation, transform.Scale, mesh.Material, (int)entity);
			}*/
			auto sprite_group = m_Registry.group<Transform>(entt::get<SpriteRenderer>);
			for (auto entity : sprite_group) {
				auto& [transform, sprite] = sprite_group.get<Transform, SpriteRenderer>(entity);
				Renderer::DrawQuad(transform.Position, transform.Rotation, transform.Scale, sprite.Material, (int)entity);
			}
			Renderer::EndScene();
		}
	}
	void Scene::OnUpdateEditor(TimerSystem ts, Ref<EulerCamera> editorCamera)
	{
		Renderer::BeginScene(editorCamera);
		/*auto group = m_Registry.group<Transform>(entt::get<MeshRenderer>);
		for (auto entity : group) {
			auto& [transform, mesh] = group.get<Transform, MeshRenderer>(entity);
			Renderer::DrawCube(transform.Position, transform.Rotation, transform.Scale, mesh.Material, (int)entity);
		}*/

		auto sprite_group = m_Registry.group<Transform>(entt::get<SpriteRenderer>);
		//KINK_CORE_INFO("SpriteCount:{0}", sprite_group.size());
		for (auto entity : sprite_group) {
			auto& [transform, sprite] = sprite_group.get<Transform, SpriteRenderer>(entity);
			Renderer::DrawQuad(transform.Position, transform.Rotation, transform.Scale, sprite.Material, (int)entity);
		}
		Renderer::EndScene();
	}
	void Scene::OnViewportResize(int width, int height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;
		auto view = m_Registry.view<Camera>();
		for (auto entity: view) {
			auto& camera_com = view.get<Camera>(entity);
			if (!camera_com.isFixedAspectRatio) {
				camera_com.RendererCamera->SetViewportSize(float(m_ViewportWidth), float(m_ViewportHeight));
			}
		}
	}
	GameObject Scene::GetGameObject(unsigned int UUID)
	{
		return GameObject();
	}
	GameObject Scene::GetPrimaryCamera() {
		auto view = m_Registry.view<Camera>();
		for (auto entity : view) {
			const auto& camera_com = view.get<Camera>(entity);
			if (camera_com.isPrimary) {
				return GameObject{ entity, this };
			}
		}
		return {};
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
	void Scene::OnComponentAdded<IDCom>(GameObject obj, IDCom& component) {
	}
	template<>
	void Scene::OnComponentAdded<Profile>(GameObject obj, Profile& component) {
	}
	template<>
	void Scene::OnComponentAdded<Transform>(GameObject obj, Transform& component) {
		
	}
	template<>
	void Scene::OnComponentAdded<Camera>(GameObject obj, Camera& component) {
		//KINK_CORE_ERROR("viewport_size:{0}, {1}", m_ViewportWidth, m_ViewportHeight);
		component.RendererCamera->SetViewportSize((float)m_ViewportWidth, (float)m_ViewportHeight);
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
	void Scene::OnComponentAdded<SpriteRenderer>(GameObject obj, SpriteRenderer& component) {
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
	template<>
	void Scene::OnComponentAdded<Rigidbody2D>(GameObject obj, Rigidbody2D& component) {
	}
	template<>
	void Scene::OnComponentAdded<BoxCollider2D>(GameObject obj, BoxCollider2D& component) {
	}
}