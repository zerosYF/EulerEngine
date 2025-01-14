#pragma once
#include "RendererAPI.h"
#include "RenderCmd.h"
namespace EulerEngine {
	class Renderer {
	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const class std::shared_ptr<VertexArray>& vertexArray);
		inline static RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }
	};
}