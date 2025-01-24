#include"gkpch.h"
#include"Renderer.h"
#include"RenderCmd.h"
#include"Platform/OpenGL/GLShader.h"
namespace EulerEngine {
	Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();
	void Renderer::Init()
	{
		RenderCommand::Init();
	}
	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(Ref<VertexArray>& vertexArray, Ref<EulerShader>& shader, Ref<Material>& material, const glm::mat4& transform=glm::mat4(1.0f))
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetMat4("u_Transform", transform);
		material->Apply();
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}