#pragma once
#include"glm/glm.hpp"
namespace EulerEngine {
	struct Transform{
		glm::vec3 Position{0.0f};
		glm::vec3 Rotation{0.0f};
		glm::vec3 Scale{1.0f};
		Transform() = default;
		Transform(const Transform& other) = default;
		Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
			:Position(position), Rotation(rotation), Scale(scale) {}
	}; 
}