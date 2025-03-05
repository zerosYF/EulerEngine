#pragma once
#include"glm/glm.hpp"
namespace EulerEngine {
	struct BoxCollider2D {
		glm::vec2 Offset = glm::vec2(0.0f, 0.0f);
		glm::vec2 Size = glm::vec2(1.0f, 1.0f);
		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		bool IsTrigger = false;
		b2ShapeId ShapeId;
		BoxCollider2D() = default;
		BoxCollider2D(const BoxCollider2D&) = default;
	};
}