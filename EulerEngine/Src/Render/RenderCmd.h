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
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
			m_RendererAPI->DrawIndexed(vertexArray);
		}
		inline static void Draw(const std::shared_ptr<VertexArray>& vertexArray) {
			m_RendererAPI->Draw(vertexArray);
		}
	private:
		static RendererAPI* m_RendererAPI;

	};
}
