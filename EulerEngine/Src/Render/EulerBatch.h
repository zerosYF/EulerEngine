#pragma once
#include"Render/EulerBuffer.h"
#include"Render/RawData/EulerVertices.h"
#include"Render/RawData/EulerMesh.h"
#include"Render/RawData/EulerMaterial.h"
#include"Render/RawData/EulerMaterial2D.h"
#include"Render/EulerShader.h"
#include<array>
#define MAX_TEXTURE_SLOTS 32
#define MAX_CUBE_COUNT 10000
#define MAX_PLANE_COUNT 10000
#define MAX_SPHERE_COUNT 10000
#define MAX_SPRITE_COUNT 10000
#define MAX_LINE_COUNT 50000
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

		struct PlaneBatchData {
			const unsigned int MaxVertices = MAX_PLANE_COUNT * PLANE_VERTEX_CNT;
			const unsigned int MaxIndices = MAX_PLANE_COUNT * PLANE_INDEX_CNT;
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
		
		struct SpriteBatchData {
			const unsigned int MaxVertices = MAX_SPRITE_COUNT * SPRITE_VERTEX_CNT;
			const unsigned int MaxIndices = MAX_SPRITE_COUNT * SPRITE_INDEX_CNT;
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
			float LineWidth = 2.0f;
		};
		static Scope<CubeBatchData> s_CubeData;
		static Scope<PlaneBatchData> s_PlaneData;
		static Scope<SpriteBatchData> s_SpriteData;
		static Scope<LineBatchData> s_LineData;
	public:
		static void Init();
		static void Shutdown();
		static void SubmitCube(const glm::mat4& model, const glm::mat4&view, const glm::mat4&projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial>& material, const int objID);
		static void SubmitSphere(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial>& material, const int objID);
		static void SubmitPlane(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial>& material, const int objID);
		static void SubmitSprite(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial2D>& material, const int objID);
		static void SubmitModel(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial>& material, const int objID);
		static void SubmitLine(const glm::mat4& view, const glm::mat4& projection, const glm::vec3 start, const glm::vec3 end, const glm::vec4 color, int objID);
		static void Clear();
		static unsigned int Flush();
	private:
		static void InitCubeData();
		static void InitPlaneData();
		static void InitSpriteData();
		static void InitLineData();
		static unsigned int FlushCubeData();
		static unsigned int FlushPlaneData();
		static unsigned int FlushSpriteData();
		static unsigned int FlushLineData();
	};
}