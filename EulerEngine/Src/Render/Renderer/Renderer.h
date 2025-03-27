#pragma once
#include"RendererAPI.h"
#include"RenderCmd.h"
#include"Render/EulerShader.h"
#include"Render/RawData/EulerMaterial.h"
#include"Render/RawData/EulerVertices.h"
#include"Render/Camera/EulerCamera.h"
#include"Render/RawData/EulerMesh.h"
#include"Render/EulerBatch.h"
#define QUAD_VERTEX_CNT 4
#define CUBE_VERTEX_CNT 8
#define QUAD_INDEX_CNT 6
#define CUBE_INDEX_CNT 24
#define CIRCLE_VERTEX_CNT 12
namespace EulerEngine {
	class Renderer {
	public:
		static void Init();
		static void ShutDown();
		static void BeginScene(const EulerCamera& camera);
		static void EndScene();
		inline static RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }

		static void DrawCube(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial>& material, int objID);

		static void DrawSprite(const glm::vec2 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial2D>& material, int objID);
		static void DrawSprite(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial2D>& material, int objID);
	
		static void DrawLine(const glm::vec3 start, const glm::vec3 end, const glm::vec4 color, int objID = -1);
		static void DrawRect(const glm::vec2 position, const glm::vec3 size, const glm::vec4 color, int objID = -1);
		static void DrawRect(const glm::vec3 position, const glm::vec3 size, const glm::vec4 color, int objID = -1);
		static void DrawRect(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color, int objID = -1);
		static void DrawCircle(const glm::vec2 position, const float radius, const glm::vec4 color, int objID = -1);
		static void DrawCircle(const glm::vec3 position, const float radius, const glm::vec4 color, int objID = -1);
		static void DrawCircle(const glm::vec2 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color, int objID = -1);
		static void DrawCircle(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color, int objID = -1);
	public:
		struct Statistics {
			unsigned int DrawCalls = 0;
			unsigned int CubeCount = 0;
			unsigned int QuadCount = 0;
			unsigned int CircleCount = 0;
			unsigned int RectCount = 0;
			unsigned int LineCount = 0;
			unsigned int GetTotalVertexCount() { return CubeCount * CUBE_VERTEX_CNT + QuadCount * QUAD_VERTEX_CNT + CircleCount * QUAD_VERTEX_CNT; }
			unsigned int GetTotalIndicesCount() { return CubeCount * CUBE_INDEX_CNT + QuadCount * QUAD_INDEX_CNT + CircleCount * QUAD_INDEX_CNT; }
		};
		struct RenderData {
			glm::mat4 ViewMatrix = glm::mat4(1.0f);
			glm::mat4 ProjectionMatrix = glm::mat4(1.0f);
			Statistics Stats;
		};
		static void ResetStatistic();
		static Statistics GetStats();
		static Scope<RenderData> s_RenderData;
	};
}