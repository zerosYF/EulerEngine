#pragma once
#include "Render/Renderer/RendererAPI.h"

namespace EulerEngine {
	class GLRendererAPI : public RendererAPI {
	public:
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void Draw(const std::shared_ptr<VertexArray>& vertexArray, const unsigned int vertex_cnt) override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, const unsigned int index_cnt) override;
	};
}