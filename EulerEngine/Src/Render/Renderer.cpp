#include"gkpch.h"
#include"Renderer.h"
#include"RenderCmd.h"
#include"Platform/OpenGL/GLShader.h"
#include"Render2D/Renderer2D.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();
	void Renderer::Init()
	{
		RenderCommand::Init();

		m_SceneData->Cube_VA = EulerEngine::VertexArray::Create();

		m_SceneData->Cube_VB = EulerEngine::VertexBuffer::Create(m_SceneData->MaxVertices * sizeof(EulerEngine::CubeVertex));

		EulerEngine::BufferLayout layout = {
			{EulerEngine::ShaderDataType::Float3, "aPosition"},
			{EulerEngine::ShaderDataType::Float2, "aTexCoord"},
		};
		m_SceneData->Cube_VB->SetLayout(layout);
		m_SceneData->Cube_VA->AddVertexBuffer(m_SceneData->Cube_VB);

		m_SceneData->CubeVertexBase = new EulerEngine::CubeVertex[m_SceneData->MaxVertices];

		m_SceneData->ResourceLib.LoadShader("common", "Shaders/Camera/first_test.glsl");
		auto texture2D = m_SceneData->ResourceLib.LoadTexture2D("texture1", "Assets/mytextures/container2.png");
		auto material = m_SceneData->ResourceLib.LoadMaterial("first");
		material->AddTexture("container", texture2D);
	}
	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		m_SceneData->ViewMatrix = camera.GetViewMatrix();
		m_SceneData->ProjectionMatrix = camera.GetProjectionMatrix();

		m_SceneData->CubeVertexArrayPtr = m_SceneData->CubeVertexBase;
	}
	void Renderer::EndScene()
	{
		Flush();
	}
	void Renderer::Flush() {
		unsigned int size = m_SceneData->CubeVertexArrayPtr - m_SceneData->CubeVertexBase;
		m_SceneData->Cube_VB->SetData(m_SceneData->CubeVertexBase, size * sizeof(EulerEngine::CubeVertex));
		RenderCommand::Draw(m_SceneData->Cube_VA, size); 
	}
	void Renderer::DrawCube(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color) {

		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		model = glm::rotate(model, glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, scale);

		for (unsigned int i = 0; i < CUBE_VERTEX_CNT; i++) {
			unsigned int head_index = CUBE_DATA_SIZE * i;
			glm::vec4 VerticePosition 
				= glm::vec4(EulerEngine::CubeVertices[head_index], EulerEngine::CubeVertices[head_index + 1], EulerEngine::CubeVertices[head_index + 2], 1.0f);
			m_SceneData->CubeVertexArrayPtr->Position = model * VerticePosition;
			m_SceneData->CubeVertexArrayPtr->TexCoord = glm::vec2(EulerEngine::CubeVertices[head_index + 3], EulerEngine::CubeVertices[head_index + 4]);
			m_SceneData->CubeVertexArrayPtr++;
		}
		auto shader = m_SceneData->ResourceLib.GetShader("common");
		auto material_ref = m_SceneData->ResourceLib.GetMaterial("first");
		material_ref->SetColor(color);

		shader->Bind();
		shader->SetMat4("view", m_SceneData->ViewMatrix);
		shader->SetMat4("projection", m_SceneData->ProjectionMatrix);
		shader->SetMat4("model", model);
		material_ref->Apply(shader);
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