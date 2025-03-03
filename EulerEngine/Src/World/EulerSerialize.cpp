#include "gkpch.h"
#include"EulerSerialize.h"
#include<yaml-cpp/yaml.h>
#include"EulerObject.h"
#include"Component/Component.h"
#include"Resource/ResourceLibrary.h"
namespace YAML {
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

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene): m_Scene(scene)
	{
	}
	static void SerializeGameObject(GameObject gameObj, YAML::Emitter& out)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "GameObject" << YAML::Value << "12093821903";
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

			out << YAML::Key << "CameraType" << YAML::Value << (int)gameObj.GetComponent<Camera>().RendererCamera->GetCameraType();
			out << YAML::Key << "ViewportWidth" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetViewportSize().first;
			out << YAML::Key << "ViewportHeight" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetViewportSize().second;
			out << YAML::Key << "Perspective_FOV" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetFovAngle();
			out << YAML::Key << "Perspective_NearClip" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetPerspectiveNearClip();
			out << YAML::Key << "Perspective_FarClip" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetPerspectiveFarClip(); 
			out << YAML::Key << "Orthographic_Size" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetZoomLevel();
			out << YAML::Key << "Orthographic_NearClip" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetOrthographicNearClip();
			out << YAML::Key << "Orthographic_FarClip" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetOrthographicFarClip();
			out << YAML::EndMap;
		}
		if (gameObj.HasComponent<MeshRenderer>()) {
			out << YAML::Key << "MeshRenderer";
			out << YAML::BeginMap;
			auto material = gameObj.GetComponent<MeshRenderer>().Material;
			if (material) {
				out << YAML::Key << "Shader" << YAML::Value << material->GetShader()->GetPath();
				out << YAML::Key << "Color" << YAML::Value << material->GetColor();
				out << YAML::Key << "TexturePath" << YAML::Value << material->GetTexture()->GetPath();
			}
			out << YAML::EndMap;
		}
		if (gameObj.HasComponent<SpriteRenderer>()) {
			out << YAML::Key << "SpriteRenderer";
			out << YAML::BeginMap;
			auto material = gameObj.GetComponent<SpriteRenderer>().Material;
			if (material) {
				out << YAML::Key << "Shader" << YAML::Value << material->GetShader()->GetPath();
				out << YAML::Key << "Color" << YAML::Value << material->GetColor();
				out << YAML::Key << "TexturePath" << YAML::Value << material->GetTexture()->GetPath();
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
					std::string uuid = gameObject["GameObject"].as<std::string>();

					KINK_CORE_INFO("Deserializing GameObject: {0}", uuid);
					std::string objName;
					if (gameObject["Profile"]) {
						objName = gameObject["Profile"]["Tag"].as<std::string>();
						KINK_CORE_INFO("Deserializing Profile: {0}", objName);
					}
					GameObject gameObj = m_Scene->CreateObject(objName);

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

						camera.RendererCamera->SetCameraType(type);
						camera.RendererCamera->SetViewportSize(gameObject["Camera"]["ViewportWidth"].as<float>(), gameObject["Camera"]["ViewportHeight"].as<float>());
						camera.RendererCamera->SetFovAngle(gameObject["Camera"]["Perspective_FOV"].as<float>());
						camera.RendererCamera->SetPerspectiveNearClip(gameObject["Camera"]["Perspective_NearClip"].as<float>());
						camera.RendererCamera->SetPerspectiveFarClip(gameObject["Camera"]["Perspective_FarClip"].as<float>());
						camera.RendererCamera->SetZoomLevel(gameObject["Camera"]["Orthographic_Size"].as<float>());
						camera.RendererCamera->SetOrthographicNearClip(gameObject["Camera"]["Orthographic_NearClip"].as<float>());
						camera.RendererCamera->SetOrthographicFarClip(gameObject["Camera"]["Orthographic_FarClip"].as<float>());
					}
					if (gameObject["MeshRenderer"]) {
						auto& meshRenderer = gameObj.AddComponent<MeshRenderer>();

						Ref<EulerMaterial> material = CreateRef<EulerMaterial>();
						material->SetShader(ResourceLibrary::GetResourceLibrary()->LoadShader("",gameObject["MeshRenderer"]["Shader"].as<std::string>()));
						material->SetColor(gameObject["MeshRenderer"]["Color"].as<glm::vec4>());
						material->SetTexture(ResourceLibrary::GetResourceLibrary()->LoadTexture2D("",gameObject["MeshRenderer"]["TexturePath"].as<std::string>()));
						meshRenderer.Material = material;
					}
					if (gameObject["SpriteRenderer"]) {
						auto& spriteRenderer = gameObj.AddComponent<SpriteRenderer>();

						Ref<EulerMaterial> material = CreateRef<EulerMaterial>();
						material->SetShader(ResourceLibrary::GetResourceLibrary()->LoadShader("", gameObject["MeshRenderer"]["Shader"].as<std::string>()));
						material->SetColor(gameObject["MeshRenderer"]["Color"].as<glm::vec4>());
						material->SetTexture(ResourceLibrary::GetResourceLibrary()->LoadTexture2D("", gameObject["MeshRenderer"]["TexturePath"].as<std::string>()));
						spriteRenderer.Material = material;
					}
				}
			}
		}
		return false;
	}
	bool SceneSerializer::DeserializeRuntime(const std::string& filePath)
	{
		KINK_CORE_ASSERT(false, "Runtime deserialization is not supported");
		return false;
	}
}