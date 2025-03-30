#include "gkpch.h"
#include"EulerSerialize.h"
#include<yaml-cpp/yaml.h>
#include"EulerObject.h"
#include"Component/Component.h"
#include"Resource/ResourceLibrary.h"
#include"Render/RawData/EulerMesh.h"
#include"Script/ScriptEngine.h"
#include"Project/EulerProject.h"
namespace YAML {
	template<>
	struct convert<glm::vec2> {
		static Node encode(const glm::vec2 vec) {
			Node node;
			node.push_back(vec.x);
			node.push_back(vec.y);
			return node;
		}
		static bool decode(const Node& node, glm::vec2& vec) {
			if (!node.IsSequence() || node.size() != 2) {
				return false;
			}
			vec.x = node[0].as<float>();
			vec.y = node[1].as<float>();
			return true;
		}
	};
	template<>
	struct convert<glm::vec3> {
		static Node encode(const glm::vec3 vec) {
			Node node;
			node.push_back(vec.x);
			node.push_back(vec.y);
			node.push_back(vec.z);
			return node;
		}
		static bool decode(const Node& node, glm::vec3& vec) {
			if (!node.IsSequence() || node.size() != 3) {
				return false;
			}
			vec.x = node[0].as<float>();
			vec.y = node[1].as<float>();
			vec.z = node[2].as<float>();
			return true;
		}
	};
	template<>
	struct convert<glm::vec4> {
		static Node encode(const glm::vec4 vec) {
			Node node;
			node.push_back(vec.x);
			node.push_back(vec.y);
			node.push_back(vec.z);
			node.push_back(vec.w);
			return node;
		}
		static bool decode(const Node& node, glm::vec4& vec) {
			if (!node.IsSequence() || node.size() != 4) {
				return false;
			}
			vec.x = node[0].as<float>();
			vec.y = node[1].as<float>();
			vec.z = node[2].as<float>();
			vec.w = node[3].as<float>();
			return true;
		}
	};
}
namespace EulerEngine {
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;
	}
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v) {
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	static std::string Rigidbody2DTypeToString(Rigidbody2D::BodyType type)
	{
		switch (type)
		{
		case Rigidbody2D::BodyType::Static:
			return "Static";
		case Rigidbody2D::BodyType::Dynamic:
			return "Dynamic";
		case Rigidbody2D::BodyType::Kinematic:
			return "Kinematic";
		default:
			return "Unknown";
		}
	}

	static Rigidbody2D::BodyType StringToRigidbody2DType(const std::string& type)
	{
		if (type == "Static") 
			return Rigidbody2D::BodyType::Static;
		else if (type == "Dynamic")
			return Rigidbody2D::BodyType::Dynamic;
		else if (type == "Kinematic")
			return Rigidbody2D::BodyType::Kinematic;
		else
			return Rigidbody2D::BodyType::Static;
	}

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene): m_Scene(scene)
	{
	}
	static void SerializeGameObject(GameObject gameObj, YAML::Emitter& out)
	{
		KINK_CORE_ASSERT(gameObj.HasComponent<IDCom>(), "GameObject must have IDComponent");
		out << YAML::BeginMap;
		out << YAML::Key << "GameObject" << YAML::Value << gameObj.GetUUID();
		if (gameObj.HasComponent<Profile>()) {
			out << YAML::Key << "Profile";
			out << YAML::BeginMap;
			out << YAML::Key << "Tag" << YAML::Value << gameObj.GetComponent<Profile>().Tag;
			out << YAML::EndMap;
		}
		if (gameObj.HasComponent<Transform>()) {
			out << YAML::Key << "Transform";
			out << YAML::BeginMap;
			out << YAML::Key << "Position" << YAML::Value << gameObj.GetComponent<Transform>().Position;
			out << YAML::Key << "Rotation" << YAML::Value << gameObj.GetComponent<Transform>().Rotation;
			out << YAML::Key << "Scale" << YAML::Value << gameObj.GetComponent<Transform>().Scale;
			out << YAML::EndMap;
		}
		if (gameObj.HasComponent<Camera>()) {
			out << YAML::Key << "Camera";
			out << YAML::BeginMap;
			out << YAML::Key << "IsPrimary" << YAML::Value << gameObj.GetComponent<Camera>().isPrimary;
			out << YAML::Key << "IsFixedAspectRatio" << YAML::Value << gameObj.GetComponent<Camera>().isFixedAspectRatio;

			out << YAML::Key << "CameraType" << YAML::Value << (int)gameObj.GetComponent<Camera>().RendererCamera.GetCameraType();
			out << YAML::Key << "ViewportWidth" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera.GetViewportSize().first;
			out << YAML::Key << "ViewportHeight" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera.GetViewportSize().second;
			out << YAML::Key << "Perspective_FOV" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera.GetFovAngle();
			out << YAML::Key << "Perspective_NearClip" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera.GetPerspectiveNearClip();
			out << YAML::Key << "Perspective_FarClip" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera.GetPerspectiveFarClip(); 
			out << YAML::Key << "Orthographic_Size" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera.GetZoomLevel();
			out << YAML::Key << "Orthographic_NearClip" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera.GetOrthographicNearClip();
			out << YAML::Key << "Orthographic_FarClip" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera.GetOrthographicFarClip();
			out << YAML::EndMap;
		}
		if (gameObj.HasComponent<MeshFilter>()) {
			out << YAML::Key << "MeshFilter";
			out << YAML::BeginMap;
			out << YAML::Key << "MeshType" << YAML::Value << EulerMesh::MeshTypeToString(gameObj.GetComponent<MeshFilter>().Type);
			out << YAML::EndMap;
		}
		if (gameObj.HasComponent<MeshRenderer>()) {
			out << YAML::Key << "MeshRenderer";
			out << YAML::BeginMap;
			auto material = gameObj.GetComponent<MeshRenderer>().Material;
			if (material) {
				out << YAML::Key << "Shader" << YAML::Value << ResourceLibrary::GetShaderInnerPath(material->GetShader());
				//
				out << YAML::Key << "TexturePath" << YAML::Value << ResourceLibrary::GetTexture2DResourcePath(material->GetTexture());
			}
			out << YAML::EndMap;
		}
		if (gameObj.HasComponent<SpriteRenderer>()) {
			out << YAML::Key << "SpriteRenderer";
			out << YAML::BeginMap;
			auto material = gameObj.GetComponent<SpriteRenderer>().Material;
			if (material) {
				out << YAML::Key << "Shader" << YAML::Value << ResourceLibrary::GetShaderInnerPath(material->GetShader());
				out << YAML::Key << "Color" << YAML::Value << material->GetColor();
				out << YAML::Key << "TexturePath" << YAML::Value << ResourceLibrary::GetTexture2DResourcePath(material->GetTexture());
			}
			out << YAML::EndMap;
		}
		if (gameObj.HasComponent<Rigidbody2D>()) {
			out << YAML::Key << "Rigidbody2D";
			out << YAML::BeginMap;
			out << YAML::Key << "Type" << YAML::Value << Rigidbody2DTypeToString(gameObj.GetComponent<Rigidbody2D>().Type);
			out << YAML::Key << "FixedRotation" << YAML::Value << gameObj.GetComponent<Rigidbody2D>().FixedRotation;
			out << YAML::Key << "Mass" << YAML::Value << gameObj.GetComponent<Rigidbody2D>().Mass;
			out << YAML::Key << "LinearDamping" << YAML::Value << gameObj.GetComponent<Rigidbody2D>().LinearDamping;
			out << YAML::Key << "AngularDamping" << YAML::Value << gameObj.GetComponent<Rigidbody2D>().AngularDamping;
			out << YAML::EndMap;
		}
		if (gameObj.HasComponent<BoxCollider2D>()) {
			out << YAML::Key << "BoxCollider2D";
			out << YAML::BeginMap;
			out << YAML::Key << "Offset" << YAML::Value << gameObj.GetComponent<BoxCollider2D>().Offset;
			out << YAML::Key << "Size" << YAML::Value << gameObj.GetComponent<BoxCollider2D>().Size;
			out << YAML::Key << "Density" << YAML::Value << gameObj.GetComponent<BoxCollider2D>().Density;
			out << YAML::Key << "Friction" << YAML::Value << gameObj.GetComponent<BoxCollider2D>().Friction;
			out << YAML::Key << "Restitution" << YAML::Value << gameObj.GetComponent<BoxCollider2D>().Restitution;
			out << YAML::Key << "IsTrigger" << YAML::Value << gameObj.GetComponent<BoxCollider2D>().IsTrigger;
			out << YAML::EndMap;
		}
		if (gameObj.HasComponent<CircleCollider2D>()) {
			out << YAML::Key << "CircleCollider2D";
			out << YAML::BeginMap;
			out << YAML::Key << "Offset" << YAML::Value << gameObj.GetComponent<CircleCollider2D>().Offset;
			out << YAML::Key << "Radius" << YAML::Value << gameObj.GetComponent<CircleCollider2D>().Radius;
			out << YAML::Key << "Density" << YAML::Value << gameObj.GetComponent<CircleCollider2D>().Density;
			out << YAML::Key << "Friction" << YAML::Value << gameObj.GetComponent<CircleCollider2D>().Friction;
			out << YAML::Key << "Restitution" << YAML::Value << gameObj.GetComponent<CircleCollider2D>().Restitution;
			out << YAML::Key << "IsTrigger" << YAML::Value << gameObj.GetComponent<CircleCollider2D>().IsTrigger;
			out << YAML::EndMap;
		}
		if (gameObj.HasComponent<CSharpScript>()) {
			out << YAML::Key << "CSharpScript";
			out << YAML::BeginMap;
			std::string ScriptClassName = gameObj.GetComponent<CSharpScript>().Name;
			out << YAML::Key << "ClassName" << YAML::Value << ScriptClassName;
			Ref<ScriptClass> obj_cls = ScriptEngine::GetGameObjectClass(ScriptClassName);
			const auto& cls_fields = obj_cls->GetFields();
			if (cls_fields.size() > 0) {
				out << YAML::Key << "ScriptFields" << YAML::Value;
				auto& obj_fields = ScriptEngine::GetScriptFieldMap(gameObj);
				out << YAML::BeginSeq;
				for (const auto& [name, field] : cls_fields) {
					if (obj_fields.find(name) == obj_fields.end()) {
						continue;
					}
					out << YAML::BeginMap;
					out << YAML::Key << "Name" << YAML::Value << name;
					out << YAML::Key << "Type" << YAML::Value << ScriptClass::ScriptFieldTypeToString(field.Type);
					out << YAML::Key << "Data" << YAML::Value;
#define FIELD_TYPE(FieldType, Type) case FieldType: out << obj_fields[name].GetData<Type>(); break;

					switch (field.Type)
					{
						FIELD_TYPE(ScriptFieldType::Int, int32_t)
						FIELD_TYPE(ScriptFieldType::UInt, uint32_t)
						FIELD_TYPE(ScriptFieldType::Long, int64_t)
						FIELD_TYPE(ScriptFieldType::ULong, uint64_t)
						FIELD_TYPE(ScriptFieldType::Short, int16_t)
						FIELD_TYPE(ScriptFieldType::UShort, uint16_t)
						FIELD_TYPE(ScriptFieldType::Byte, int8_t)
						FIELD_TYPE(ScriptFieldType::UByte, uint8_t)
						FIELD_TYPE(ScriptFieldType::Float, float)
						FIELD_TYPE(ScriptFieldType::Double, double)
						FIELD_TYPE(ScriptFieldType::Bool, bool)
						FIELD_TYPE(ScriptFieldType::Char, char)
						FIELD_TYPE(ScriptFieldType::String, std::string)
						FIELD_TYPE(ScriptFieldType::Vector2, glm::vec2)
						FIELD_TYPE(ScriptFieldType::Vector3, glm::vec3)
						FIELD_TYPE(ScriptFieldType::Vector4, glm::vec4)
						FIELD_TYPE(ScriptFieldType::GameObject, uint64_t)
					}
					out << YAML::EndMap;
				}
				out << YAML::EndSeq;
			}
			out << YAML::EndMap;
		}
		out << YAML::EndMap;
	}
	void SceneSerializer::Serialize(const std::string& filePath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled";
		out << YAML::Key << "GameObjects" << YAML::Value << YAML::BeginSeq;
		m_Scene->m_Registry.view<Profile>().each([&](auto entity, auto& tc) {
			GameObject gameObject{ entity, m_Scene.get() };
			if (!gameObject) {
				return;
			}
			SerializeGameObject(gameObject, out);
		});
		out << YAML::EndSeq;
		out << YAML::EndMap;
		std::ofstream fout(filePath);
		fout << out.c_str();
		fout.close();
	}
	void SceneSerializer::SerializeRuntime(const std::string& filePath)
	{
		KINK_CORE_ASSERT(false,"Runtime serialization is not supported");
	}
	bool SceneSerializer::Deserialize(const std::string& filePath)
	{
		std::ifstream stream(filePath);
		std::stringstream strStream;
		strStream << stream.rdbuf();
		YAML::Node data = YAML::Load(strStream.str());
		if (data["Scene"]) {
			std::string sceneName = data["Scene"].as<std::string>();
			KINK_CORE_INFO("Deserializing scene: {0}", sceneName);
			auto gameObjects = data["GameObjects"];
			if (gameObjects) {
				for (auto gameObject : gameObjects) {
					uint64_t uuid = gameObject["GameObject"].as<uint64_t>();

					std::string objName;
					if (gameObject["Profile"]) {
						objName = gameObject["Profile"]["Tag"].as<std::string>();
					}
					GameObject gameObj = m_Scene->CreateObject(uuid, objName);
					KINK_CORE_INFO("Deserializing GameObject: {0}", objName);

					if (gameObject["Transform"]) {
						auto& transform = gameObj.GetComponent<Transform>();
						transform.Position = gameObject["Transform"]["Position"].as<glm::vec3>();
						transform.Rotation = gameObject["Transform"]["Rotation"].as<glm::vec3>();
						transform.Scale = gameObject["Transform"]["Scale"].as<glm::vec3>();
					}
					if (gameObject["Camera"]) {
						auto type = (CameraType)gameObject["Camera"]["CameraType"].as<int>();
						auto& camera = gameObj.AddComponent<Camera>(type);
						camera.isPrimary = gameObject["Camera"]["IsPrimary"].as<bool>();
						camera.isFixedAspectRatio = gameObject["Camera"]["IsFixedAspectRatio"].as<bool>();

						camera.RendererCamera.SetCameraType(type);
						camera.RendererCamera.SetViewportSize(gameObject["Camera"]["ViewportWidth"].as<float>(), gameObject["Camera"]["ViewportHeight"].as<float>());
						camera.RendererCamera.SetFovAngle(gameObject["Camera"]["Perspective_FOV"].as<float>());
						camera.RendererCamera.SetPerspectiveNearClip(gameObject["Camera"]["Perspective_NearClip"].as<float>());
						camera.RendererCamera.SetPerspectiveFarClip(gameObject["Camera"]["Perspective_FarClip"].as<float>());
						camera.RendererCamera.SetZoomLevel(gameObject["Camera"]["Orthographic_Size"].as<float>());
						camera.RendererCamera.SetOrthographicNearClip(gameObject["Camera"]["Orthographic_NearClip"].as<float>());
						camera.RendererCamera.SetOrthographicFarClip(gameObject["Camera"]["Orthographic_FarClip"].as<float>());
					}
					if (gameObject["MeshFilter"]) {
						auto& meshFilter = gameObj.AddComponent<MeshFilter>();
						std::string meshType = gameObject["MeshFilter"]["MeshType"].as<std::string>();
						meshFilter.Type = EulerMesh::StringToMeshType(meshType);
					}
					if (gameObject["MeshRenderer"]) {
						auto& meshRenderer = gameObj.AddComponent<MeshRenderer>();

						Ref<EulerMaterial3D> material = CreateRef<EulerMaterial3D>();
						material->SetShader(ResourceLibrary::LoadShader(gameObject["MeshRenderer"]["Shader"].as<std::string>()));
						//
						material->SetTexture(ResourceLibrary::LoadTexture2D(gameObject["MeshRenderer"]["TexturePath"].as<std::string>()));
						meshRenderer.Material = material;
					}
					if (gameObject["SpriteRenderer"]) {
						auto& spriteRenderer = gameObj.AddComponent<SpriteRenderer>();

						Ref<EulerMaterial2D> material = CreateRef<EulerMaterial2D>();
						material->SetShader(ResourceLibrary::LoadShader(gameObject["SpriteRenderer"]["Shader"].as<std::string>()));
						material->SetColor(gameObject["SpriteRenderer"]["Color"].as<glm::vec4>());
						material->SetTexture(ResourceLibrary::LoadTexture2D(gameObject["SpriteRenderer"]["TexturePath"].as<std::string>()));
						spriteRenderer.Material = material;
					}
					if (gameObject["Rigidbody2D"]) {
						auto& rigidbody2D = gameObj.AddComponent<Rigidbody2D>();
						rigidbody2D.Type = StringToRigidbody2DType(gameObject["Rigidbody2D"]["Type"].as<std::string>());
						rigidbody2D.FixedRotation = gameObject["Rigidbody2D"]["FixedRotation"].as<bool>();
						rigidbody2D.Mass = gameObject["Rigidbody2D"]["Mass"].as<float>();
						rigidbody2D.LinearDamping = gameObject["Rigidbody2D"]["LinearDamping"].as<float>();
						rigidbody2D.AngularDamping = gameObject["Rigidbody2D"]["AngularDamping"].as<float>();
					}
					if (gameObject["BoxCollider2D"]) {
						auto& boxCollider2D = gameObj.AddComponent<BoxCollider2D>();
						boxCollider2D.Offset = gameObject["BoxCollider2D"]["Offset"].as<glm::vec2>();
						boxCollider2D.Size = gameObject["BoxCollider2D"]["Size"].as<glm::vec2>();
						boxCollider2D.Density = gameObject["BoxCollider2D"]["Density"].as<float>();
						boxCollider2D.Friction = gameObject["BoxCollider2D"]["Friction"].as<float>();
						boxCollider2D.Restitution = gameObject["BoxCollider2D"]["Restitution"].as<float>();
						boxCollider2D.IsTrigger = gameObject["BoxCollider2D"]["IsTrigger"].as<bool>();
					}
					if (gameObject["CircleCollider2D"]) {
						auto& circleCollider2D = gameObj.AddComponent<CircleCollider2D>();
						circleCollider2D.Offset = gameObject["CircleCollider2D"]["Offset"].as<glm::vec2>();
						circleCollider2D.Radius = gameObject["CircleCollider2D"]["Radius"].as<float>();
						circleCollider2D.Density = gameObject["CircleCollider2D"]["Density"].as<float>();
						circleCollider2D.Friction = gameObject["CircleCollider2D"]["Friction"].as<float>();
						circleCollider2D.Restitution = gameObject["CircleCollider2D"]["Restitution"].as<float>();
						circleCollider2D.IsTrigger = gameObject["CircleCollider2D"]["IsTrigger"].as<bool>();
					}
					if (gameObject["CSharpScript"]) {
						auto& cSharpScript = gameObj.AddComponent<CSharpScript>();
						cSharpScript.Name = gameObject["CSharpScript"]["ClassName"].as<std::string>();
						auto script_fields = gameObject["CSharpScript"]["ScriptFields"];
						if (script_fields) {
							Ref<ScriptClass> obj_cls = ScriptEngine::GetGameObjectClass(cSharpScript.Name);
							if (obj_cls) {
								const auto& cls_fields = obj_cls->GetFields();
								auto& obj_fields = ScriptEngine::GetScriptFieldMap(gameObj);
								for (auto script_field : script_fields) {
									std::string name = script_field["Name"].as<std::string>();
									ScriptFieldType type = ScriptClass::StringToScriptFieldType(script_field["Type"].as<std::string>());

									ScriptFieldInstance& field_instance = obj_fields[name];
									if (cls_fields.find(name) == cls_fields.end()) {
										continue;
									}
									field_instance.Field = cls_fields.at(name);
#define FIELD_TYPE_RE(FieldType, Type) case FieldType: field_instance.SetData<Type>(script_field["Data"].as<Type>()); break;
									switch (type) {
										FIELD_TYPE_RE(ScriptFieldType::Int, int32_t)
										FIELD_TYPE_RE(ScriptFieldType::UInt, uint32_t)
										FIELD_TYPE_RE(ScriptFieldType::Long, int64_t)
										FIELD_TYPE_RE(ScriptFieldType::ULong, uint64_t)
										FIELD_TYPE_RE(ScriptFieldType::Short, int16_t)
										FIELD_TYPE_RE(ScriptFieldType::UShort, uint16_t)
										FIELD_TYPE_RE(ScriptFieldType::Byte, int8_t)
										FIELD_TYPE_RE(ScriptFieldType::UByte, uint8_t)
										FIELD_TYPE_RE(ScriptFieldType::Float, float)
										FIELD_TYPE_RE(ScriptFieldType::Double, double)
										FIELD_TYPE_RE(ScriptFieldType::Bool, bool)
										FIELD_TYPE_RE(ScriptFieldType::Char, char)
										FIELD_TYPE_RE(ScriptFieldType::String, std::string)
										FIELD_TYPE_RE(ScriptFieldType::Vector2, glm::vec2)
										FIELD_TYPE_RE(ScriptFieldType::Vector3, glm::vec3)
										FIELD_TYPE_RE(ScriptFieldType::Vector4, glm::vec4)
										FIELD_TYPE_RE(ScriptFieldType::GameObject, uint64_t)
									}
								}
							}
						}
					}
				}
			}
		}
		return true;
	}
	bool SceneSerializer::DeserializeRuntime(const std::string& filePath)
	{
		KINK_CORE_ASSERT(false, "Runtime deserialization is not supported");
		return false;
	}
}