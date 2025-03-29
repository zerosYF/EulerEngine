#pragma once
#include"Render/RawData/EulerMaterial.h"
#include"Render/RawData/EulerMesh.h"
#include"MeshFilter.h"
#include"glm/glm.hpp"
namespace EulerEngine {
	struct MeshRenderer{
		Ref<EulerMaterial> Material;
		MeshRenderer() = default;
		MeshRenderer(const MeshRenderer&) = default;
		MeshRenderer(const Ref<EulerMaterial> material) : Material(material) {}
		Ref<EulerMaterial> GetMaterial() const { return Material; }
	};
}