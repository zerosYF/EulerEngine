#pragma once
#include<string>
#include<vector>
namespace EulerEngine {
	class ComponentInfoRes {
	public:
		std::string m_name;
		std::string  m_component;
	};
	class ObjectInfoRes {
	public:

	};
	class ObjectInstanceRes {
	public:
		std::string m_name;
		std::string m_info;
	};
}