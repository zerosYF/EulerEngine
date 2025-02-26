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
		glm::mat4 GetTransform() const {
			glm::mat4 transform = glm::mat4(1.0f);
			transform = glm::translate(transform, Position);
			transform = glm::rotate(transform, glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			transform = glm::rotate(transform, glm::radians(Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, Scale);
			return transform;
		}
	}; 
}