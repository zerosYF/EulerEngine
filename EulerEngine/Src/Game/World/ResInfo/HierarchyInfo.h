#pragma once
#include<string>
#include<vector>
#include"../../../Math/EulerMath.h"
#include"ObjectInfo.h"
namespace EulerEngine {
	class HierarchyRes {
	public:
		std::vector<ObjectInstanceRes> m_objects;
	};
}