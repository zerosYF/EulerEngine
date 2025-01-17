#pragma once
#include"RendererAPI.h"
#include"RenderCmd.h"
#include"EulerCamera.h"
#include"EulerShader.h"
namespace EulerEngine {
	class Renderer {
	public:
		static void BeginScene(Camera& camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<EulerShader>& shader, const glm::mat4& transform);
		inline static RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }
	public:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;

		};
		static SceneData* m_SceneData;
	};
}