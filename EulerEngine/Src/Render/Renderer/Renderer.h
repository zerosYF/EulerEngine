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
#define QUAD_INDEX_CNT 6
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
	public:
		struct Statistics {
			unsigned int DrawCalls = 0;
			unsigned int CubeCount = 0;
			unsigned int QuadCount = 0;
			unsigned int GetTotalVertexCount() { return CubeCount * CUBE_VERTEX_CNT + QuadCount * QUAD_VERTEX_CNT; }
			unsigned int GetTotalIndicesCount() { return CubeCount * 8; }
		};
		static void ResetStatistic();
		static Statistics GetStats();

		struct SceneData {
			glm::mat4 ViewMatrix = glm::mat4(1.0f);
			glm::mat4 ProjectionMatrix = glm::mat4(1.0f);

			const unsigned int MaxVertices =  MAX_QUAD_COUNT * QUAD_VERTEX_CNT;
			const unsigned int MaxIndices = MAX_QUAD_COUNT * QUAD_INDEX_CNT;

			Ref<VertexArray> Cube_VA;
			CubeVertex* CubeVertexBase = nullptr;
			CubeVertex* CubeVertexArrayPtr = nullptr;
			Ref<VertexBuffer> Cube_VB;

			Ref<VertexArray> Quad_VA;
			QuadVertex* QuadVertexBase = nullptr;
			QuadVertex* QuadVertexArrayPtr = nullptr;
			Ref<VertexBuffer> Quad_VB;

			std::array<Ref<Texture2D>, MAX_TEXTURE_SLOTS> TextureSlots;
			unsigned int TextureSlotIndex = 0;

			Statistics stats;
		};
		static Scope<SceneData> m_SceneData;
	};
}