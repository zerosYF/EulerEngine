#include "gkpch.h"
#include"EulerSerialize.h"
#include<yaml-cpp/yaml.h>
#include"EulerObject.h"
#include"Component/Component.h"
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
			out << YAML::Key << "CameraType" << YAML::Value << (int)gameObj.GetComponent<Camera>().RendererCamera->GetCameraType();
			out << YAML::Key << "AspectRatio" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetAspectRatio();
			out << YAML::Key << "FOV" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetFovAngle();
			out << YAML::Key << "NearClip" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetPerspectiveNearClip();
			out << YAML::Key << "FarClip" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetPerspectiveFarClip(); 
			out << YAML::Key << "Size" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetZoomLevel();
			out << YAML::Key << "NearClip" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetOrthographicNearClip();
			out << YAML::Key << "FarClip" << YAML::Value << gameObj.GetComponent<Camera>().RendererCamera->GetOrthographicFarClip();
			out << YAML::EndMap;
		}
		/*if (gameObj.HasComponent<MeshRenderer>()) {
			out << YAML::Key << "MeshRenderer";
			out << YAML::BeginMap;
			out << YAML::Key << "Material" << YAML::Value << gameObj.GetComponent<MeshRenderer>().Material;
			out << YAML::EndMap;
		}*/
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
					unsigned int uuid = gameObject["GameObject"].as<unsigned int>();

					KINK_CORE_INFO("Deserializing GameObject: {0}", uuid);
					if (gameObject["Profile"]) {
						std::string tag = gameObject["Profile"]["Tag"].as<std::string>();
						KINK_CORE_INFO("Deserializing Profile: {0}", tag);
					}
					if (gameObject["Transform"]) {
						glm::vec3 position = gameObject["Transform"]["Position"].as<glm::vec3>();
						glm::vec3 rotation = gameObject["Transform"]["Rotation"].as<glm::vec3>();
						glm::vec3 scale = gameObject["Transform"]["Scale"].as<glm::vec3>();
						//KINK_CORE_INFO("Deserializing Transform: {0}, {1}, {2}", position, rotation, scale);
					}
					if (gameObject["Camera"]) {
						int cameraType = gameObject["Camera"]["CameraType"].as<int>();
						float aspectRatio = gameObject["Camera"]["AspectRatio"].as<float>();
						float fov = gameObject["Camera"]["FOV"].as<float>();
						float nearClip = gameObject["Camera"]["NearClip"].as<float>();
						float farClip = gameObject["Camera"]["FarClip"].as<float>();
						float size = gameObject["Camera"]["Size"].as<float>();
						float orthographicNearClip = gameObject["Camera"]["OrthographicNearClip"].as<float>();
						float orthographicFarClip = gameObject["Camera"]["OrthographicFarClip"].as<float>();
						//KINK_CORE_INFO("Deserializing Camera: {0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}", cameraType, aspectRatio, fov, nearClip, farClip, size, orthographicNearClip, orthographicFarClip);
					}
					//if (gameObject["MeshRenderer"]) {
					//	std::string material = gameObject["MeshRenderer"]["Material"].as<std::string>();
					//	//KINK_CORE_INFO("Deserializing MeshRenderer: {0}", material);
					//}
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