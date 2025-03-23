#include"gkpch.h"
#include"ProjectSerializer.h"
#include<fstream>
#include<yaml-cpp/yaml.h>
namespace EulerEngine {
	ProjectSerializer::ProjectSerializer(Ref<Project> project): m_Project(project)
	{

	}
	bool ProjectSerializer::Serialize(const std::filesystem::path& filePath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		{
			out << YAML::Key << "Project" << YAML::Value;
			out << YAML::BeginMap;
			{
				out << YAML::Key << "Name" << YAML::Value << m_Project->GetConfig().m_ProjectName;
				out << YAML::Key << "StartScene" << YAML::Value << m_Project->GetConfig().m_StartScene.string();
				out << YAML::Key << "AssetDirectory" << YAML::Value << m_Project->GetConfig().m_AssetDirectory.string();
				out << YAML::Key << "ScriptModulePath" << YAML::Value << m_Project->GetConfig().m_ScriptModulePath.string();
			}
			out << YAML::EndMap;
		}
		out << YAML::EndMap;

		std::ofstream fout(filePath);
		fout << out.c_str();
		fout.close();
		return true;
	}
	bool ProjectSerializer::Deserialize(const std::filesystem::path& filePath)
	{
		YAML::Node data;
		try {
			data = YAML::LoadFile(filePath.string());
		}
		catch (const YAML::ParserException& e) {
			return false;
		}
		if (!data["Project"]) {
			return false;
		}
		m_Project->GetConfig().m_ProjectName = data["Project"]["Name"].as<std::string>();
		m_Project->GetConfig().m_StartScene = data["Project"]["StartScene"].as<std::string>();
		m_Project->GetConfig().m_AssetDirectory = data["Project"]["AssetDirectory"].as<std::string>();
		m_Project->GetConfig().m_ScriptModulePath = data["Project"]["ScriptModulePath"].as<std::string>();
		return true;
	}
}