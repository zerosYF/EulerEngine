#include"gkpch.h"
#include"Renderer.h"
#include"RenderCmd.h"
#include"Platform/OpenGL/GLShader.h"
#include"Core/Logs/EulerLog.h"
#include"Resource/ResourceLibrary.h"
#include <glm\gtx\quaternion.hpp>
namespace EulerEngine {
	Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();
	void Renderer::Init()
	{
		RenderCommand::Init();

		/*m_SceneData->Cube_VA = EulerEngine::VertexArray::Create();
		m_SceneData->Cube_VB = EulerEngine::VertexBuffer::Create(m_SceneData->MaxVertices * sizeof(EulerEngine::CubeVertex));
		EulerEngine::BufferLayout cube_layout = {
			{EulerEngine::ShaderDataType::Float3, "aPosition"},
			{EulerEngine::ShaderDataType::Float2, "aTexCoord"},
			{EulerEngine::ShaderDataType::Int, "aGameObjectID"},
		};
		m_SceneData->Cube_VB->SetLayout(cube_layout);
		m_SceneData->Cube_VA->AddVertexBuffer(m_SceneData->Cube_VB);
		m_SceneData->CubeVertexBase = new EulerEngine::CubeVertex[m_SceneData->MaxVertices];*/


		unsigned offset = 0;
		unsigned int SquareIndices[QUAD_INDEX_CNT] = { 0, 1, 2, 2, 3, 0 };
		unsigned int* QuadIndices = new unsigned int[m_SceneData->MaxIndices];
		for (unsigned int i = 0; i < m_SceneData->MaxIndices; i += QUAD_INDEX_CNT) {
			for (unsigned int j = 0; j < QUAD_INDEX_CNT; j++) {
				QuadIndices[i + j] = offset + SquareIndices[j];
			}
			offset += 4;
		}

		m_SceneData->Quad_VA = EulerEngine::VertexArray::Create();
		m_SceneData->Quad_VB = EulerEngine::VertexBuffer::Create(m_SceneData->MaxVertices * sizeof(EulerEngine::QuadVertex));
		EulerEngine::BufferLayout quad_layout = {
			{EulerEngine::ShaderDataType::Float3, "aPosition"},
			{EulerEngine::ShaderDataType::Float2, "aTexCoord"},
			{EulerEngine::ShaderDataType::Int, "aGameObjectID"},
		};
		m_SceneData->Quad_VB->SetLayout(quad_layout);
		m_SceneData->Quad_VA->AddVertexBuffer(m_SceneData->Quad_VB);
		EulerEngine::Ref<EulerEngine::IndexBuffer> indexBuffer
			= EulerEngine::IndexBuffer::Create(QuadIndices, m_SceneData->MaxIndices);
		m_SceneData->Quad_VA->SetIndexBuffer(indexBuffer);
		m_SceneData->QuadVertexBase = new EulerEngine::QuadVertex[m_SceneData->MaxVertices];


		for (unsigned int i = 0; i < m_SceneData->TextureSlots.size(); i++) {
			m_SceneData->TextureSlots[i] = 0;
		}
	}
	void Renderer::ShutDown()
	{
		delete[] m_SceneData->CubeVertexBase;
		delete[] m_SceneData->QuadVertexBase;
	}
	void Renderer::BeginScene(Ref<EulerCamera> camera)
	{
		m_SceneData->ViewMatrix = camera->GetViewMatrix();
		m_SceneData->ProjectionMatrix = camera->GetProjectionMatrix();

		m_SceneData->CubeVertexArrayPtr = m_SceneData->CubeVertexBase;

		m_SceneData->QuadVertexArrayPtr = m_SceneData->QuadVertexBase;

		m_SceneData->TextureSlotIndex = 0;
	}
	void Renderer::EndScene()
	{
		Flush();
	}
	void Renderer::Flush() {
		/*unsigned int size = m_SceneData->CubeVertexArrayPtr - m_SceneData->CubeVertexBase;
		m_SceneData->Cube_VB->SetData(m_SceneData->CubeVertexBase, size * sizeof(EulerEngine::CubeVertex));

		for (unsigned int i = 0; i < m_SceneData->TextureSlotIndex; i++) {
			m_SceneData->TextureSlots[i]->Bind(i);
		}

		RenderCommand::Draw(m_SceneData->Cube_VA, size); */

		unsigned int size = m_SceneData->QuadVertexArrayPtr - m_SceneData->QuadVertexBase;
		m_SceneData->Quad_VB->SetData(m_SceneData->QuadVertexBase, size * sizeof(EulerEngine::QuadVertex));

		for (unsigned int i = 0; i < m_SceneData->TextureSlotIndex; i++) {
			m_SceneData->TextureSlots[i]->Bind(i);
		}

		RenderCommand::Draw(m_SceneData->Quad_VA, size);
		m_SceneData->stats.DrawCalls++;
	}

	void Renderer::DrawCube(const Ref<EulerShader> shader, const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color, const Ref<Texture2D>& texture, int objID)
	{
		auto material = EulerMaterial::Create();
		material->SetShader(shader);
		material->SetColor(color);
		material->SetTexture(texture);
		DrawCube(position, rotation, scale, material, objID);
	}
	void Renderer::DrawCube(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<EulerMaterial>& material, int objID)
	{
		auto shader = material->GetShader();
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
		model *= glm::toMat4(glm::quat(rotation));
		model = glm::scale(model, scale);

		for (unsigned int i = 0; i < CUBE_VERTEX_CNT; i++) {
			unsigned int head_index = CUBE_DATA_SIZE * i;
			glm::vec4 VerticePosition
				= glm::vec4(EulerEngine::CubeVertices[head_index], EulerEngine::CubeVertices[head_index + 1], EulerEngine::CubeVertices[head_index + 2], 1.0f);
			m_SceneData->CubeVertexArrayPtr->Position = model * VerticePosition;
			m_SceneData->CubeVertexArrayPtr->TexCoord = glm::vec2(EulerEngine::CubeVertices[head_index + 3], EulerEngine::CubeVertices[head_index + 4]);
			m_SceneData->CubeVertexArrayPtr->GameObjectID = objID;
			m_SceneData->CubeVertexArrayPtr++;
		}

		shader->Bind();
		shader->SetMat4("view", m_SceneData->ViewMatrix);
		shader->SetMat4("projection", m_SceneData->ProjectionMatrix);
		shader->SetInt("texture_index", textureIndex);
		shader->SetVec4("color", material->GetColor());

		m_SceneData->stats.CubeCount++;
	}

	void Renderer::DrawQuad(const glm::vec2 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<EulerMaterial>& material, int objID)
	{
		DrawQuad({ position.x, position.y, 0.0f }, rotation, scale, material, objID);
	}
	void Renderer::DrawQuad(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<EulerMaterial>& material, int objID)
	{
		auto shader = material->GetShader();
		int samplers[MAX_TEXTURE_SLOTS];
		for (unsigned int i = 0; i < MAX_TEXTURE_SLOTS; i++) {
			samplers[i] = i;
		}
		shader->SetIntArray("sampler2D", samplers, MAX_TEXTURE_SLOTS);

		auto texture = material->GetTexture();
		if (texture != nullptr) {

		}
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
		model *= glm::toMat4(glm::quat(rotation));
		model = glm::scale(model, scale);

		for (unsigned int i = 0; i < QUAD_VERTEX_CNT; i++) {
			unsigned int head_index = QUAD_DATA_SIZE * i;
			glm::vec4 VerticePosition
				= glm::vec4(EulerEngine::QuadVertices[head_index], EulerEngine::QuadVertices[head_index + 1], EulerEngine::QuadVertices[head_index + 2], 1.0f);
			m_SceneData->QuadVertexArrayPtr->Position = model * VerticePosition;
			m_SceneData->QuadVertexArrayPtr->TexCoord = glm::vec2(EulerEngine::QuadVertices[head_index + 3], EulerEngine::QuadVertices[head_index + 4]);
			m_SceneData->QuadVertexArrayPtr->GameObjectID = objID;
			m_SceneData->QuadVertexArrayPtr++;
		}

		shader->Bind();
		shader->SetMat4("view", m_SceneData->ViewMatrix);
		shader->SetMat4("projection", m_SceneData->ProjectionMatrix);
		shader->SetInt("texture_index", textureIndex);
		shader->SetVec4("color", material->GetColor());

		m_SceneData->stats.QuadCount++;
	}

	void Renderer::ResetStatistic()
	{
		memset(&m_SceneData->stats, 0, sizeof(Statistics));
	}

	Renderer::Statistics Renderer::GetStats()
	{
		return m_SceneData->stats;
	}


	void Renderer::Submit(Ref<VertexArray>& vertexArray, Ref<EulerShader>& shader, glm::vec4 color, Ref<Texture2D> texture,
		const glm::mat4& model=glm::mat4(1.0f), const unsigned int vertex_cnt = 0)
	{
		shader->Bind();
		shader->SetMat4("view", m_SceneData->ViewMatrix);
		shader->SetMat4("projection", m_SceneData->ProjectionMatrix);
		shader->SetMat4("model", model);
		texture->Bind(0);
		vertexArray->Bind();
		RenderCommand::Draw(vertexArray, vertex_cnt);
	}
}