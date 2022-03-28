#pragma once
#include<glad/glad.h>
#include<ft2build.h>
#include"EulerMath.h"
#define EULER_WIDTH 800
#define EULER_HEIGHT 600
namespace EulerEngine {
	class EulerMain {
	public:
		// …„œÒª˙≈‰÷√
		//Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
	public:
		EulerMain() {}
		void Run();
	};
}