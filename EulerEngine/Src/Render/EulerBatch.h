#pragma once
#include"Render/EulerBuffer.h"
#include"Render/RawData/EulerMesh.h"
#include"Render/RawData/EulerMaterial.h"
#include"Render/RawData/EulerMaterial2D.h"
#include"Render/EulerShader.h"
#include<array>
#define MAX_TEXTURE_SLOTS 32
#define MAX_CUBE_COUNT 10000
#define MAX_QUAD_COUNT 10000
#define MAX_LINE_COUNT 50000
#define QUAD_VERTEX_CNT 4
#define CUBE_VERTEX_CNT 8
#define QUAD_INDEX_CNT 6
#define CUBE_INDEX_CNT 24
#define LINE_VERTEX_CNT 2
namespace EulerEngine{
	class EulerBatch {
	private:
		struct CubeBatchData {
			const unsigned int MaxVertices = MAX_CUBE_COUNT * CUBE_VERTEX_CNT;
			const unsigned int MaxIndices = MAX_CUBE_COUNT * CUBE_INDEX_CNT;
			Ref<VertexArray> VA;
			Vertex* VertexBase = nullptr;
			Vertex* VertexArrayPtr = nullptr;
			Ref<VertexBuffer> VB;
			Ref<IndexBuffer> IB;
			unsigned int VertexCount = 0;
			unsigned int IndexCount = 0;
			Ref<EulerShader> Shader;
			std::vector<unsigned int> SingleIndices;

			std::array<Ref<Texture2D>, MAX_TEXTURE_SLOTS> Texture2DSlots;
			unsigned int Texture2DSlotLoadedCount = 0;
		};
		
		struct QuadBatchData {
			const unsigned int MaxVertices = MAX_QUAD_COUNT * QUAD_VERTEX_CNT;
			const unsigned int MaxIndices = MAX_QUAD_COUNT * QUAD_INDEX_CNT;
			Ref<VertexArray> VA;
			SpriteVertex* VertexBase = nullptr;
			SpriteVertex* VertexArrayPtr = nullptr;
			Ref<VertexBuffer> VB;
			Ref<IndexBuffer> IB;
			unsigned int VertexCount = 0;
			unsigned int IndexCount = 0;
			Ref<EulerShader> Shader;
			std::vector<unsigned int> SingleIndices;

			std::array<Ref<Texture2D>, MAX_TEXTURE_SLOTS> Texture2DSlots;
			unsigned int Texture2DSlotLoadedCount = 0;
		};

		struct LineBatchData {
			const unsigned int MaxVertices = MAX_LINE_COUNT * LINE_VERTEX_CNT;
			Ref<VertexArray> VA;
			LineVertex* VertexBase = nullptr;
			LineVertex* VertexArrayPtr = nullptr;
			Ref<VertexBuffer> VB;
			unsigned int VertexCount = 0;
			Ref<EulerShader> Shader;
			float LineWidth = 10.0f;
		};
		static Scope<CubeBatchData> s_CubeData;
		static Scope<QuadBatchData> s_QuadData;
		static Scope<LineBatchData> s_LineData;
	public:
		static void Init();
		static void Shutdown();
		static void SubmitCube(const glm::mat4& model, const glm::mat4&view, const glm::mat4&projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial>& material, const int objID);
		static void SubmitSphere(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial>& material, const int objID);
		static void SubmitQuad(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial2D>& material, const int objID);
		static void SubmitModel(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial>& material, const int objID);
		static void SubmitLine(const glm::mat4& view, const glm::mat4& projection, const glm::vec3 start, const glm::vec3 end, const glm::vec4 color, int objID);
		static void Clear();
		static unsigned int Flush();
	private:
		static void InitCubeData();
		static void InitQuadData();
		static void InitLineData();
	};
}