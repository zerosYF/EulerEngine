#pragma once
#include"Render/RawData/EulerMaterial2D.h"
#include"Render/RawData/EulerMesh.h"
#include"glm/glm.hpp"
namespace EulerEngine {
	struct SpriteRenderer {
		Ref<EulerMaterial2D> Material;
		Ref<EulerMesh> Mesh;
		SpriteRenderer() = default;
		SpriteRenderer(const SpriteRenderer&) = default;
		SpriteRenderer(const Ref<EulerMaterial2D> material) : Material(material) {}

	};
}
