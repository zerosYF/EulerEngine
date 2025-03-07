#pragma once
#include"RendererAPI.h"
#include"RenderCmd.h"
#include"Render/EulerShader.h"
#include"Render/EulerMaterial.h"
#include"Render/Vertices/EulerVertices.h"
#include"Render/Camera/EulerCamera.h"
#define MAX_TEXTURE_SLOTS 32
#define MAX_CUBE_COUNT 10000
#define MAX_QUAD_COUNT 10000
#define QUAD_VERTEX_CNT 4
#define CUBE_VERTEX_CNT 8
#define QUAD_INDEX_CNT 6
#define CUBE_INDEX_CNT 36
namespace EulerEngine {
	class Renderer {
	public:
		static void Init();
		static void ShutDown();
		static void BeginScene(Ref<EulerCamera> camera);
		static void EndScene();
		static void Flush();
		static void Submit(Ref<VertexArray>& vertexArray, Ref<EulerShader>& shader, glm::vec4 color, Ref<Texture2D> texture, const glm::mat4& model,const unsigned int vertex_cnt);
		inline static RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }

		static void DrawCube(const Ref<EulerShader> shader, const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color, const Ref<Texture2D>& texture, int objID);
		static void DrawCube(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<EulerMaterial>& material, int objID);

		static void DrawQuad(const glm::vec2 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<EulerMaterial>& material, int objID);
		static void DrawQuad(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<EulerMaterial>& material, int objID);

		static void DrawCircle(const glm::vec2 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color, float thickness, float fade, int objID);
		static void DrawCircle(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color, float thickness, float fade, int objID);
	public:
		struct Statistics {
			unsigned int DrawCalls = 0;
			unsigned int CubeCount = 0;
			unsigned int QuadCount = 0;
			unsigned int CircleCount = 0;
			unsigned int GetTotalVertexCount() { return CubeCount * CUBE_VERTEX_CNT + QuadCount * QUAD_VERTEX_CNT + CircleCount * QUAD_VERTEX_CNT; }
			unsigned int GetTotalIndicesCount() { return CubeCount * CUBE_INDEX_CNT + QuadCount * QUAD_INDEX_CNT + CircleCount * QUAD_INDEX_CNT; }
		};
		static void ResetStatistic();
		static Statistics GetStats();

		struct SceneData {
			glm::mat4 ViewMatrix = glm::mat4(1.0f);
			glm::mat4 ProjectionMatrix = glm::mat4(1.0f);

			const unsigned int MaxVertices =  MAX_QUAD_COUNT * QUAD_VERTICE_CNT;
			const unsigned int MaxIndices = MAX_QUAD_COUNT * QUAD_INDEX_CNT;

			Ref<VertexArray> Cube_VA;
			unsigned int CubeIndicesCount = 0;
			CubeVertex* CubeVertexBase = nullptr;
			CubeVertex* CubeVertexArrayPtr = nullptr;
			Ref<VertexBuffer> Cube_VB;

			Ref<VertexArray> Quad_VA;
			unsigned int QuadIndicesCount = 0;
			QuadVertex* QuadVertexBase = nullptr;
			QuadVertex* QuadVertexArrayPtr = nullptr;
			Ref<VertexBuffer> Quad_VB;
			Ref<EulerShader> QuadShader;

			Ref<VertexArray> Circle_VA;
			unsigned int CircleIndicesCount = 0;
			CircleVertex* CircleVertexBase = nullptr;
			CircleVertex* CircleVertexArrayPtr = nullptr;
			Ref<VertexBuffer> Circle_VB;
			Ref<EulerShader> CircleShader;

			Ref<VertexArray> Line_VA;
			unsigned int LineIndicesCount = 0;
			LineVertex* LineVertexBase = nullptr;
			LineVertex* LineVertexArrayPtr = nullptr;
			Ref<VertexBuffer> Line_VB;

			std::array<Ref<Texture2D>, MAX_TEXTURE_SLOTS> TextureSlots;
			unsigned int TextureSlotIndex = 0;

			Statistics stats;
		};
		static Scope<SceneData> m_SceneData;
	};
}