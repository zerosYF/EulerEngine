#pragma once
#include<string>
#include<filesystem>
#include"GutKink/Core.h"
namespace EulerEngine {
	struct ProjectConfig {
		std::string m_ProjectName = "EulerProject";
		std::filesystem::path m_StartScene;
		std::filesystem::path m_AssetDirectory;
		std::filesystem::path m_ScriptModulePath;
	};
	class Project {
	public:
		Project();
		static const std::filesystem::path& GetAssetDir(){
			return s_ActiveProject->m_Config.m_AssetDirectory;
		}
		static const std::filesystem::path& GetActiveProjectDir() {
			return s_ActiveProject->m_ActiveProjectDir;
		}
		static std::filesystem::path GetPath(const std::filesystem::path& path) {
			return GetActiveProjectDir() / GetAssetDir() / path;
		}
		static std::filesystem::path GetPathInActiveProjectAsset(const std::filesystem::path& path) {
			return path.lexically_relative(GetActiveProjectDir() / GetAssetDir() / "");
		}
		ProjectConfig& GetConfig() { 
			return m_Config; 
		}
		static Ref<Project> GetActive() { return s_ActiveProject; }
		static Ref<Project> New();
		static Ref<Project> Load(const std::filesystem::path&);
		static bool SaveActive(const std::filesystem::path&);
	private:
		ProjectConfig m_Config;
		std::filesystem::path m_ActiveProjectDir;
		inline static Ref<Project> s_ActiveProject;
	};
}