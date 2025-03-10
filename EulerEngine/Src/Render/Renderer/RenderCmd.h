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
		inline static void Draw(const std::shared_ptr<VertexArray>& vertexArray, const unsigned int vertex_cnt) {
			m_RendererAPI->Draw(vertexArray, vertex_cnt);
		}
		inline static void DrawLines(const std::shared_ptr<VertexArray>& vertexArray, const unsigned int vertex_cnt) {
			m_RendererAPI->DrawLines(vertexArray, vertex_cnt);
		}
		inline static void SetLineWidth(float width) {
			m_RendererAPI->SetLineWidth(width);
		}
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, const unsigned int index_count) {
			m_RendererAPI->DrawIndexed(vertexArray, index_count);
		}
	private:
		static Scope<RendererAPI> m_RendererAPI;
	};
}
