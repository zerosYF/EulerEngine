#pragma once
#include"Render/RawData/EulerMaterial.h"
#include"Render/RawData/EulerMesh.h"
#include"MeshFilter.h"
#include"glm/glm.hpp"
namespace EulerEngine {
	struct MeshRenderer{
		Ref<EulerMaterial3D> Material;
		MeshRenderer() = default;
		MeshRenderer(const MeshRenderer&) = default;
		MeshRenderer(const Ref<EulerMaterial3D> material) : Material(material) {}
		Ref<EulerMaterial3D> GetMaterial() const { return Material; }
	};
}