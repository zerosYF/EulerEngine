#pragma once
#include "RendererAPI.h"
namespace EulerEngine {
	class RenderCommand {
	public:
		inline static void Init() {
			m_RendererAPI->Init();
		}
		inline static void SetClearColor(const glm::vec4& color) {
			m_RendererAPI->SetClearColor(color);
		}
		inline static void Clear() {
			m_RendererAPI->Clear();
		}
		inline static void Draw(const std::shared_ptr<VertexArray>& vertexArray, const unsigned int vertex_cnt = 0) {
			m_RendererAPI->Draw(vertexArray, vertex_cnt);
		}
	private:
		static Scope<RendererAPI> m_RendererAPI;
	};
}
