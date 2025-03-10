#include"gkpch.h"
#include"GLRendererAPI.h"
#include"glad/glad.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	void GLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
	}
	void GLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void GLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void GLRendererAPI::Draw(const std::shared_ptr<VertexArray>& vertexArray, const unsigned int vertex_cnt)
	{
		vertexArray->Bind();
		glDrawArrays(GL_TRIANGLES, 0, vertex_cnt);
	}
	void GLRendererAPI::DrawLines(const std::shared_ptr<VertexArray>& vertexArray, const unsigned int vertex_cnt)
	{
		vertexArray->Bind();
		glDrawArrays(GL_LINES, 0, vertex_cnt);
	}

	void GLRendererAPI::SetLineWidth(float width)
	{
		glLineWidth(width);
	}

	void GLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, const unsigned int index_cnt)
	{
		unsigned int count = index_cnt ? index_cnt : vertexArray->GetIndexBuffer()->GetCount();
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}