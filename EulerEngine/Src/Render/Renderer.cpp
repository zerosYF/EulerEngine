#include"gkpch.h"
#include"Renderer.h"
#include"RenderCmd.h"
#include"Platform/OpenGL/GLShader.h"
#include"Render2D/Renderer2D.h"
namespace EulerEngine {
	Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();
	void Renderer::Init()
	{
		RenderCommand::Init();
	}
	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		m_SceneData->ViewMatrix = camera.GetViewMatrix();
		m_SceneData->ProjectionMatrix = camera.GetProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(Ref<VertexArray>& vertexArray, Ref<EulerShader>& shader, Ref<Material>& material, 
		const glm::mat4& model=glm::mat4(1.0f), const unsigned int vertex_cnt = 0)
	{
		shader->Bind();
		shader->SetMat4("view", m_SceneData->ViewMatrix);
		shader->SetMat4("projection", m_SceneData->ProjectionMatrix);
		shader->SetMat4("model", model);
		material->Apply(shader);
		vertexArray->Bind();
		RenderCommand::Draw(vertexArray, vertex_cnt);
	}
}