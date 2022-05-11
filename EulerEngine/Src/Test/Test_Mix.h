#pragma once
#include"../Math/EulerMath.h"
#include<vector>
using namespace std;
namespace EulerEngine {
	vector<glm::vec3> vegetation;
	void vegetationInit() {
		vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
		vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
		vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
		vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
		vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));
	}

}