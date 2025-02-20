#pragma once
#include"Render/EulerMaterial.h"
#include"glm/glm.hpp"
namespace EulerEngine {
	struct RendererComponent{
		glm::vec4 Color{1.0f};
		RendererComponent() = default;
		RendererComponent(const RendererComponent&) = default;
		RendererComponent(const glm::vec4 color) : Color(color) {}
		
	};
}