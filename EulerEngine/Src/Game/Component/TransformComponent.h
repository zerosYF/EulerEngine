#pragma once
#include"ComponentBase.h"
#include"glm/glm.hpp"
namespace EulerEngine {
	struct TransformComponent: public ComponentBase {
		glm::mat4 Tranform;
		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const glm::mat4& transform) :Tranform(transform) {}
	};
}