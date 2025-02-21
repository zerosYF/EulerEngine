#pragma once
#include"Render/EulerMaterial.h"
#include"glm/glm.hpp"
namespace EulerEngine {
	struct SpriteRenderer {
		Ref<EulerMaterial> Material;
		SpriteRenderer() = default;
		SpriteRenderer(const SpriteRenderer&) = default;
		SpriteRenderer(const Ref<EulerMaterial> material) : Material(material) {}

	};
}
