#pragma once
#include"RendererAPI.h"
#include"RenderCmd.h"
#include"EulerCamera.h"
#include"EulerShader.h"
#include"EulerMaterial.h"
namespace EulerEngine {
	class Renderer {
	public:
		static void Init();
		static void BeginScene(Camera& camera);
		static void EndScene();
		static void Submit(Ref<VertexArray>& vertexArray, Ref<EulerShader>& shader, Ref<Material>& material, const glm::mat4& transform);
		inline static RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }
	public:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;

		};
		static Scope<SceneData> m_SceneData;
	};
}