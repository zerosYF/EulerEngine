#pragma once
#include"glm/glm.hpp"
namespace EulerEngine {
	struct TransformComponent{
		glm::vec3 Position{0.0f};
		glm::vec3 Rotation{0.0f};
		glm::vec3 Scale{1.0f};
		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) 
			:Position(position), Rotation(rotation), Scale(scale) {}
	}; 
}