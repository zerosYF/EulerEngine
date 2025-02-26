#pragma once
#include"glm/glm.hpp"
#include <glm\gtx\quaternion.hpp>
namespace EulerEngine {
	struct Transform{
		glm::vec3 Position{0.0f};
		glm::vec3 Rotation{0.0f}; //radians
		glm::vec3 Scale{1.0f};
		Transform() = default;
		Transform(const Transform& other) = default;
		Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
			:Position(position), Rotation(rotation), Scale(scale) {}
		glm::mat4 GetTransform() const {
			glm::mat4 transform = glm::mat4(1.0f);
			transform *= glm::translate(glm::mat4(1.0f), Position);
			transform *= glm::toMat4(glm::quat(Rotation));
			transform *= glm::scale(glm::mat4(1.0f), Scale);
			return transform;
		}
	}; 
}