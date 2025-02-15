#pragma once
#include"RendererAPI.h"
#include"RenderCmd.h"
#include"Camera/EulerCamera.h"
#include"EulerShader.h"
#include"EulerMaterial.h"
#include"Vertices/EulerVertices.h"
#include"Resource/ResourceLibrary.h"
namespace EulerEngine {
	class Renderer {
	public:
		static void Init();
		static void BeginScene(PerspectiveCamera& camera);
		static void EndScene();
		static void Flush();
		static void Submit(Ref<VertexArray>& vertexArray, Ref<EulerShader>& shader, Ref<Material>& material, const glm::mat4& model, const unsigned int vertex_cnt);
		inline static RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }

		static void DrawCube(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color);
	public:
		struct SceneData {
			const unsigned int MaxCubes = 10000;
			const unsigned int MaxVertices = MaxCubes * CUBE_VERTEX_CNT;
			Ref<VertexArray> Cube_VA;
			ResourceLibrary ResourceLib;
			glm::mat4 ViewMatrix;
			glm::mat4 ProjectionMatrix;
			CubeVertex* CubeVertexBase = nullptr;
			CubeVertex* CubeVertexArrayPtr = nullptr;
			Ref<VertexBuffer> Cube_VB;
		};
		static Scope<SceneData> m_SceneData;
	};
}