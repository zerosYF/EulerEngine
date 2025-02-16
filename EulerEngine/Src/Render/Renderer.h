#pragma once
#include"RendererAPI.h"
#include"RenderCmd.h"
#include"Camera/EulerCamera.h"
#include"EulerShader.h"
#include"EulerMaterial.h"
#include"Vertices/EulerVertices.h"
#define MAX_TEXTURE_SLOTS 32
#define MAX_CUBE_COUNT 10000
namespace EulerEngine {
	class Renderer {
	public:
		static void Init();
		static void ShutDown();
		static void BeginScene(PerspectiveCamera& camera);
		static void EndScene();
		static void Flush();
		static void Submit(Ref<VertexArray>& vertexArray, Ref<EulerShader>& shader, Ref<Material>& material, const glm::mat4& model, const unsigned int vertex_cnt);
		inline static RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }

		static void DrawCube(Ref<EulerShader>& shader, const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<Material>& material);
	public:
		struct Statistics {
			unsigned int DrawCalls = 0;
			unsigned int CubeCount = 0;
			unsigned int GetTotalVertexCount() { return CubeCount * 36; }
			unsigned int GetTotalIndicesCount() { return CubeCount * 8; }
		};
		static void ResetStatistic();
		static Statistics GetStats();

		struct SceneData {
			const unsigned int MaxVertices = MAX_CUBE_COUNT * CUBE_VERTEX_CNT;
			Ref<VertexArray> Cube_VA;
			glm::mat4 ViewMatrix;
			glm::mat4 ProjectionMatrix;
			CubeVertex* CubeVertexBase = nullptr;
			CubeVertex* CubeVertexArrayPtr = nullptr;
			Ref<VertexBuffer> Cube_VB;

			std::array<Ref<Texture2D>, MAX_TEXTURE_SLOTS> TextureSlots;
			unsigned int TextureSlotIndex = 0;

			Statistics stats;
		};
		static Scope<SceneData> m_SceneData;
	};
}