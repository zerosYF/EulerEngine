#pragma once
#include<string>
#include<memory>
#include"ResInfo/ObjectInfo.h"
#include"ResInfo/WorldInfo.h"
#include"EulerHierarchy.h"
#include<unordered_map>
namespace EulerEngine {
	class WorldManager {
	public:
		void initialize();
		void clear();
		void reloadCurrentHierarchy();
		void saveCurrentHierarchy();

		void update(double deltaTime) {}
	private:
		bool loadWorld(const std::string& worldURL);
		bool loadHierarchy(const std::string& hierarchyURL);

		bool m_isLoaded{false};
		std::string m_currentWorldURL;
		std::shared_ptr<WorldRes> m_currentWorldResource;
		std::unordered_map<std::string, std::shared_ptr<Hierarchy>> m_loadedHierarchys;
		std::weak_ptr<Hierarchy> m_currentActiveHierarchy;
	};
}