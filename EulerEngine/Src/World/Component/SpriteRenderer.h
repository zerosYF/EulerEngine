#pragma once
#include"Render/RawData/EulerMaterial2D.h"
#include"glm/glm.hpp"
namespace EulerEngine {
	struct SpriteRenderer {
		Ref<EulerMaterial2D> Material;
		SpriteRenderer() = default;
		SpriteRenderer(const SpriteRenderer&) = default;
		SpriteRenderer(const Ref<EulerMaterial2D> material) : Material(material) {}

	};
}
