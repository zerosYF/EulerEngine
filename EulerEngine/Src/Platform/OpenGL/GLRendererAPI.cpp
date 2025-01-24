#include"gkpch.h"
#include"GLRendererAPI.h"
#include"glad/glad.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	void GLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void GLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void GLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void GLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		if (vertexArray->GetIndexBuffer() == nullptr) {
			//KINK_CORE_INFO("NO INDEX BUFFER,USE DRAW ARRAY...");
			Draw(vertexArray);
			return;
		}
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	void GLRendererAPI::Draw(const std::shared_ptr<VertexArray>& vertexArray) {
		glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetVertexBuffers().size());
	}
}