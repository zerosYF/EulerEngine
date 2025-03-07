#pragma once
#include"glm/glm.hpp"
namespace EulerEngine {
	struct CircleRenderer {
		glm::vec4 Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		float Thickness = 1.0f;
		float Fade = 1.0f;
		CircleRenderer() = default;
		CircleRenderer(const CircleRenderer& other) = default;
	};
}