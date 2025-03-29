#pragma once
#include"Render/RawData/EulerMesh.h"
namespace EulerEngine {
	struct MeshFilter {
		Ref<EulerMesh> Mesh; //TODO:From Serialization
		MeshType Type = MeshType::None;
		MeshFilter() = default;
		MeshFilter(MeshType type): Type(type) {
		}
		void SetMesh(Ref<EulerMesh> mesh, MeshType type) {
			this->Mesh = mesh;
		}
		Ref<EulerMesh> GetMesh() {
			return Mesh;
		}
		MeshType GetType() {
			return Type;
		}
		void SetType(MeshType type) {
			this->Type = type;
		}
	};
}