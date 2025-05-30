#include"gkpch.h"
#include"EulerScene.h"
#include"Component/Component.h"
#include"Render/Renderer/Renderer.h"
#include"EulerObject.h"
#include"EulerBehaviour.h"
#include"Resource/ResourceLibrary.h"
#include"Script/ScriptEngine.h"
#include"Jolt/Jolt.h"
#include"Jolt/Physics/PhysicsSystem.h"
#include"Jolt/Physics/Collision/Shape/BoxShape.h"
#include"Jolt/Physics/Body/BodyCreationSettings.h"
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

	Scene::Scene():m_PhysicsWorld(b2_nullWorldId)
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
			entt::entity dstEntity = entityMap.at(id);
			auto& component = src.get<Component>(e);
			dst.emplace_or_replace<Component>(dstEntity, component);
		}
	}
	template<typename Component>
	static void CopyComponent(GameObject dst, GameObject src) {
		if (src.HasComponent<Component>()) {
			dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
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
			GameObject obj = newScene ->CreateObject(id, name);
			entityMap[id] = (entt::entity)obj;
		}
		CopyComponent<Transform>(dstRegistry, srcregistry, entityMap);
		CopyComponent<BoxCollider2D>(dstRegistry, srcregistry, entityMap);
		CopyComponent<Rigidbody2D>(dstRegistry, srcregistry, entityMap);
		CopyComponent<SpriteRenderer>(dstRegistry, srcregistry, entityMap);
		CopyComponent<MeshFilter>(dstRegistry, srcregistry, entityMap );
		CopyComponent<MeshRenderer>(dstRegistry, srcregistry, entityMap);
		CopyComponent<NativeScript>(dstRegistry, srcregistry, entityMap);
		CopyComponent<Camera>(dstRegistry, srcregistry, entityMap);
		CopyComponent<CircleCollider2D>(dstRegistry, srcregistry, entityMap);
		CopyComponent<CSharpScript>(dstRegistry, srcregistry, entityMap);
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
		m_EntityMap[uuid] = go;
		return go;
	}
	void Scene::DuplicateObject(GameObject obj)
	{
		std::string name = obj.GetName() + "_copy";
		GameObject newObj = CreateObject(name);
		CopyComponent<Transform>(newObj, obj);
		CopyComponent<BoxCollider2D>(newObj, obj);
		CopyComponent<Rigidbody2D>(newObj, obj);
		CopyComponent<SpriteRenderer>(newObj, obj);
		CopyComponent<MeshFilter>(newObj, obj);
		CopyComponent<MeshRenderer>(newObj, obj);
		CopyComponent<NativeScript>(newObj, obj);
		CopyComponent<Camera>(newObj, obj);
		CopyComponent<CircleCollider2D>(newObj, obj);
		CopyComponent<CSharpScript>(newObj, obj);
	}
	void Scene::DestroyObject(GameObject obj)
	{
		KINK_CORE_WARN("Destroy OBJ:{0}", (unsigned int)obj);
		m_EntityMap.erase(obj.GetUUID());
		m_Registry.destroy(obj);
	}
	void Scene::OnRuntimeStart()
	{
		m_IsRunning = true;
		OnPhysics2DStart();
		OnCSharpScriptStart();
		OnNativeScriptStart();
	}
	void Scene::OnRuntimeStop()
	{
		OnPhysics2DStop();
		OnCSharpScriptStop();
		OnNativeScriptStop();
		m_IsRunning = false;
	}
	void Scene::OnSimulationStart()
	{
		OnPhysics2DStart();
	}
	void Scene::OnSimulationStop()
	{
		OnPhysics2DStop();
	}
	void Scene::OnUpdateRuntime()
	{
		if (!m_IsPaused || m_StepFrame-- > 0) {
			OnCSharpScriptUpdate();
			OnNativeScriptUpdate();
			OnPhysics2DUpdate();
		}

		EulerCamera* mainCamera = nullptr;
		auto group = m_Registry.group<Camera>(entt::get<Transform>);
		for (auto entity : group) {
			auto& [transform, camera] = group.get<Transform, Camera>(entity);
			if (camera.isPrimary) {
				mainCamera = &camera.RendererCamera;
				mainCamera->SetPosition(transform.Position);
				mainCamera->SetRotation(transform.Rotation);
				break;
			}
		}
		if (mainCamera) {
			RenderScene(*mainCamera);
		}
	}
	void Scene::OnUpdateSimulation(EulerCamera& editorCamera)
	{
		if (!m_IsPaused || m_StepFrame-- > 0) {
			OnPhysics2DUpdate();
		}
		RenderScene(editorCamera);
	}
	void Scene::OnUpdateEditor(EulerCamera& editorCamera)
	{
		RenderScene(editorCamera);
	}
	void Scene::OnViewportResize(int width, int height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;
		auto view = m_Registry.view<Camera>();
		for (auto entity: view) {
			auto& camera_com = view.get<Camera>(entity);
			if (!camera_com.isFixedAspectRatio) {
				camera_com.RendererCamera.SetViewportSize(float(m_ViewportWidth), float(m_ViewportHeight));
			}
		}
	}
	GameObject Scene::GetGameObject(uint64_t UUID)
	{
		if (m_EntityMap.find(UUID) != m_EntityMap.end()) {
			return GameObject{ m_EntityMap[UUID], this };
		}
		return {};
	}
	GameObject Scene::GetGameObjectByName(std::string name)
	{
		auto view = m_Registry.view<Profile>();
		for (auto e : view) {
			const auto& profile = view.get<Profile>(e);
			if (profile.Tag == name) {
				return GameObject{ e, this };
			}
		}
		return {};
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

	void Scene::Step(int frame)
	{
		m_StepFrame = frame;
	}

	void Scene::RenderScene(EulerCamera& camera)
	{
		Renderer::BeginScene(camera);
		{
			auto view = m_Registry.view<Transform, MeshFilter, MeshRenderer>();
			for (auto entity : view) {
				auto [transform, filter, renderer] = view.get<Transform, MeshFilter, MeshRenderer>(entity);
				if (filter.GetType() == MeshType::None) {
					KINK_CORE_WARN("MeshFilter has no mesh");
					continue;
				}
				std::vector<float> vertices;
				std::vector<unsigned int> indices;
				if (filter.GetType() == MeshType::Cube) {
					vertices = std::vector<float>(std::begin(CubeVertices), std::end(CubeVertices));
					//indices = std::vector<unsigned int>(std::begin(CubeIndices), std::end(CubeIndices));
				}
				else if (filter.GetType() == MeshType::Plane) {
					vertices = std::vector<float>(std::begin(PlaneVertices), std::end(PlaneVertices));
					indices = std::vector<unsigned int>(std::begin(PlaneIndices), std::end(PlaneIndices));
				}
				else if (filter.GetType() == MeshType::Sphere) {
					vertices = Generator::GenerateSphereVertices(1.0f, 16, 16);
					indices = Generator::GenerateSphereIndices(16, 16);
				}

				if (filter.Mesh == nullptr) {
					filter.Mesh = CreateRef<EulerMesh>(vertices, indices);
				}
				else {
					filter.Mesh->SetVertices(vertices);
					filter.Mesh->SetIndices(indices);
				}
				Renderer::DrawMesh(filter.Type, transform.Position, transform.Rotation, transform.Scale, filter.Mesh, renderer.Material, (int)entity);
			}
		}
		{
			auto view = m_Registry.view<Transform, SpriteRenderer>();
			for (auto entity : view) {
				auto [transform, renderer] = view.get<Transform, SpriteRenderer>(entity);
				Renderer::DrawSprite(transform.Position, transform.Rotation, transform.Scale, renderer.Mesh, renderer.Material, (int)entity);
			}
		}
		Renderer::EndScene();
	}

	void Scene::OnPhysics2DStart()
	{
		b2Vec2 gravity = b2Vec2({ 0.0f, -9.81f });
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = gravity;
		m_PhysicsWorld = b2CreateWorld(&worldDef);
		auto view = m_Registry.view<Rigidbody2D>();
		for (auto e : view) {
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
			}
			if (obj.HasComponent<CircleCollider2D>()) {
				auto& circle2d = obj.GetComponent<CircleCollider2D>();
				b2Circle circle = { {circle2d.Offset.x, circle2d.Offset.y},  circle2d.Radius };

				b2ShapeDef shapeDef = b2DefaultShapeDef();
				b2ShapeId shape = b2CreateCircleShape(body, &shapeDef, &circle);

				shapeDef.density = circle2d.Density;
				shapeDef.friction = circle2d.Friction;
				shapeDef.restitution = circle2d.Restitution;
			}
		}
	}

	void Scene::OnPhysics2DStop()
	{
		b2DestroyWorld(m_PhysicsWorld);
		m_PhysicsWorld = b2_nullWorldId;
	}


	void Scene::OnPhysics2DUpdate()
	{
		const int subSteps = 4;
		b2World_Step(m_PhysicsWorld, TimerSystem::GetDeltaTime(), subSteps);
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
		}
	}

	void Scene::OnPhysicsStart()
	{
		const unsigned int MaxBodys = 1024;
		const unsigned int NumLayers = 4;
		const unsigned int MaxBodyPairs = 1024;
		const unsigned int MaxContactConstraints = 1024;
		/*const JPH::BroadPhaseLayerInterface broadPhaseLayerInterface;
		const JPH::ObjectVsBroadPhaseLayerFilter objectVsBroadPhaseLayerFilter;
		const JPH::ObjectLayerPairFilter objectLayerPairFilter;
		JPH::PhysicsSystem physicsSystem;
		physicsSystem.Init(MaxBodys, NumLayers, MaxBodyPairs, MaxContactConstraints, 
			broadPhaseLayerInterface, objectVsBroadPhaseLayerFilter, objectLayerPairFilter);
		physicsSystem.SetGravity({ 0.0f, -9.81f, 0.0f });*/
	}

	void Scene::OnPhysicsStop()
	{
	}

	void Scene::OnPhysicsUpdate()
	{
	}

	void Scene::OnNativeScriptStart()
	{
		m_Registry.view<NativeScript>().each([=](auto entity, auto& nsc) {
			if (nsc.Instance == nullptr) {
				nsc.Instance = nsc.InstantiateScript();
				nsc.Instance->m_gameObject = GameObject{ entity, this };
				nsc.Instance->OnCreate();
			}
		});
	}

	void Scene::OnNativeScriptStop()
	{
		m_Registry.view<NativeScript>().each([=](auto entity, auto& nsc) {
			if (nsc.Instance == nullptr) {
				nsc.Instance->OnDestroy();
			}
		});
	}

	void Scene::OnNativeScriptUpdate()
	{
		m_Registry.view<NativeScript>().each([=](auto entity, auto& nsc) {
			if (nsc.Instance == nullptr) {
				nsc.Instance->OnUpdate();
			}
		});
	}

	void Scene::OnCSharpScriptStart()
	{
		ScriptEngine::OnRuntimeStart(this);
		auto view = m_Registry.view<CSharpScript>();
		for (auto e : view) {
			GameObject obj = { e, this };
			ScriptEngine::OnCreateGameObject(obj);
		}
	}

	void Scene::OnCSharpScriptStop()
	{
		auto view = m_Registry.view<CSharpScript>();
		for (auto e : view) {
			GameObject obj = { e, this };
			ScriptEngine::OnDestroyGameObject(obj);
		}
		ScriptEngine::OnRuntimeStop();
	}

	void Scene::OnCSharpScriptUpdate()
	{
		auto view = m_Registry.view<CSharpScript>();
		for (auto e : view) {
			GameObject obj = { e, this };
			ScriptEngine::OnUpdateGameObject(obj);
		}
	}


	/// <summary>
	/// template specialization for Components
	/// </summary>
	/// <param name="obj"></param>
	/// <param name="component"></param>
	template<typename T>
	void Scene::OnComponentAdded(GameObject obj, T& component) {
		static_assert(false);
	}
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
		component.RendererCamera.SetViewportSize((float)m_ViewportWidth, (float)m_ViewportHeight);
	}
	template<>
	void Scene::OnComponentAdded<MeshFilter>(GameObject obj, MeshFilter& component) {
	}
	template<>
	void Scene::OnComponentAdded<MeshRenderer>(GameObject obj, MeshRenderer& component) {
		auto shader = ResourceLibrary::LoadShader("Shaders/Default/3d_default.glsl");
		auto material = CreateRef<EulerMaterial3D>();
		material->SetShader(shader);
		component.Material = material;
	}
	template<>
	void Scene::OnComponentAdded<SpriteRenderer>(GameObject obj, SpriteRenderer& component) {
		auto shader = ResourceLibrary::LoadShader("Shaders/Default/sprite.glsl");
		auto material = CreateRef<EulerMaterial2D>();
		material->SetShader(shader);
		material->SetColor(glm::vec4(1.0f));
		component.Material = material;

		std::vector<float> spriteVertices(std::begin(SpriteVertices), std::end(SpriteVertices));
		std::vector<unsigned int> spriteIndices(std::begin(SpriteIndices), std::end(SpriteIndices));
		auto mesh = CreateRef<EulerMesh>(spriteVertices, spriteIndices);
		component.Mesh = mesh;
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
	template<>
	void Scene::OnComponentAdded<CircleCollider2D>(GameObject obj, CircleCollider2D& component) {
	}
	template<>
	void Scene::OnComponentAdded<CSharpScript>(GameObject obj, CSharpScript& component) {
	}
}