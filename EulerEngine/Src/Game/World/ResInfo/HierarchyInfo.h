#pragma once
#include<string>
#include<vector>
#include"../../../Math/EulerMath.h"
#include"ObjectInfo.h"
namespace EulerEngine {
	class HierarchyRes {
	public:
		glm::vec3 m_gravity{0.f,0.f,-9.8f};
		std::vector<ObjectInstanceRes> m_objects;
	};
}