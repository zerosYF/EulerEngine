#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/matrix_decompose.hpp>
#include<glm/gtc/type_ptr.hpp>
namespace EulerEngine { 
	namespace Math {
		bool DecomposeTransform(const glm::mat4& transform, glm::vec3& outPosition, glm::vec3& outRotation, glm::vec3& outScale);
	}
}