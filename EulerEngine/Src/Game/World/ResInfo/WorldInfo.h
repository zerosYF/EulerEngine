#pragma once
#include<string>
#include<vector>
namespace EulerEngine {
	class WorldRes {
	public:
		std::string m_name;
		std::vector<std::string> m_hierarchyURLs;
		std::string  m_defaultHierarchy;
	};
}