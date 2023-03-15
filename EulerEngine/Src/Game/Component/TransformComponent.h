#pragma once
#include"ComponentBase.h"
#include"../../Math/EulerMath.h"
class TransformComponent {
	glm::vec3 position;
	void tick();
};