#include"gkpch.h"
#include"Renderer.h"
#include"RenderCmd.h"
#include"Platform/OpenGL/GLShader.h"
namespace EulerEngine {
	Renderer::SceneData* m_SceneData = new Renderer::SceneData;
	void Renderer::Init()
	{
		RenderCommand::Init();
	}
	void Renderer::BeginScene(Camera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<EulerShader>& shader, const glm::mat4& transform=glm::mat4(1.0f))
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->setMat4("u_Transform", transform);

		material->Bind();

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}