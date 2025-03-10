#pragma once
#include"glm/glm.hpp"
namespace EulerEngine {
	struct CircleCollider2D {
		glm::vec2 Offset = glm::vec2(0.0f, 0.0f);
		float Radius = 1.0f;
		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;   
		bool IsTrigger = false;
		CircleCollider2D() = default;
		CircleCollider2D(const CircleCollider2D&) = default;
	};
}