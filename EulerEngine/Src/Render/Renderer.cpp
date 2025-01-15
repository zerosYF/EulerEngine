#include"gkpch.h"
#include"Renderer.h"
#include"RenderCmd.h"
namespace EulerEngine {
	Renderer::SceneData* m_SceneData = new Renderer::SceneData;
	void Renderer::BeginScene(Camera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<EulerShader>& shader)
	{
		shader->Bind();
		shader->setMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}