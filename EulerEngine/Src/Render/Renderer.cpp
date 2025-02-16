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


		for (unsigned int i = 0; i < m_SceneData->TextureSlots.size(); i++) {
			m_SceneData->TextureSlots[i] = 0;
		}
	}
	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		m_SceneData->ViewMatrix = camera.GetViewMatrix();
		m_SceneData->ProjectionMatrix = camera.GetProjectionMatrix();

		m_SceneData->CubeVertexArrayPtr = m_SceneData->CubeVertexBase;
		m_SceneData->TextureSlotIndex = 0;
	}
	void Renderer::EndScene()
	{
		Flush();
	}
	void Renderer::Flush() {
		unsigned int size = m_SceneData->CubeVertexArrayPtr - m_SceneData->CubeVertexBase;
		m_SceneData->Cube_VB->SetData(m_SceneData->CubeVertexBase, size * sizeof(EulerEngine::CubeVertex));

		for (unsigned int i = 0; i < m_SceneData->TextureSlotIndex; i++) {
			m_SceneData->TextureSlots[i]->Bind(i);
		}

		RenderCommand::Draw(m_SceneData->Cube_VA, size); 
	}

	void Renderer::DrawCube(Ref<EulerShader>& shader, const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<Material>& material)
	{
		int samplers[MAX_TEXTURE_SLOTS];
		for (unsigned int i = 0; i < MAX_TEXTURE_SLOTS; i++) {
			samplers[i] = i;
		}
		shader->SetIntArray("sampler2D", samplers, MAX_TEXTURE_SLOTS);

		auto texture = material->GetTexture();

		float textureIndex = 0.0f;

		for (unsigned int i = 1; i < m_SceneData->TextureSlotIndex; i++) {
			if (*m_SceneData->TextureSlots[i] == *texture) {
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f) {
			textureIndex = (float)m_SceneData->TextureSlotIndex;
			m_SceneData->TextureSlots[m_SceneData->TextureSlotIndex] = texture;
			m_SceneData->TextureSlotIndex++;
		}

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

		shader->Bind();
		shader->SetMat4("view", m_SceneData->ViewMatrix);
		shader->SetMat4("projection", m_SceneData->ProjectionMatrix);
		shader->SetMat4("model", model);
		shader->SetInt("texture_index", textureIndex);
	}


	void Renderer::Submit(Ref<VertexArray>& vertexArray, Ref<EulerShader>& shader, Ref<Material>& material, 
		const glm::mat4& model=glm::mat4(1.0f), const unsigned int vertex_cnt = 0)
	{
		shader->Bind();
		shader->SetMat4("view", m_SceneData->ViewMatrix);
		shader->SetMat4("projection", m_SceneData->ProjectionMatrix);
		shader->SetMat4("model", model);
		material->Apply(shader, 0);
		vertexArray->Bind();
		RenderCommand::Draw(vertexArray, vertex_cnt);
	}
}