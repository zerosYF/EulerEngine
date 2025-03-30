#pragma once
#include"Render/EulerBuffer.h"
#include"Render/RawData/EulerVertices.h"
#include"Render/RawData/EulerMesh.h"
#include"Render/RawData/EulerMaterial.h"
#include"Render/RawData/EulerMaterial2D.h"
#include"Render/EulerShader.h"
#include"Render/Batch/BatchData.h"
#include<array>
#define LINE_VERTEX_CNT 2
#define MAX_CUBE_COUNT 1000
#define MAX_PLANE_COUNT 1000
#define MAX_SPHERE_COUNT 1000
#define MAX_SPRITE_COUNT 1000
#define MAX_LINE_COUNT 5000
namespace EulerEngine{
	class EulerBatch {
	public:
		static void Init();
		static void Shutdown();
		static void SubmitCube(const glm::mat4& model, const glm::mat4&view, const glm::mat4&projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial3D>& material, const int objID);
		static void SubmitSphere(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial3D>& material, const int objID);
		static void SubmitPlane(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial3D>& material, const int objID);
		static void SubmitSprite(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial2D>& material, const int objID);
		static void SubmitModel(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial3D>& material, const int objID);
		static void SubmitLine(const glm::mat4& view, const glm::mat4& projection, const glm::vec3 start, const glm::vec3 end, const glm::vec4 color, int objID);
		static void Clear();
		static unsigned int Flush();
	};
}