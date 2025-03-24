#include"gkpch.h"
#include"Renderer.h"
#include"RenderCmd.h"
#include"Platform/OpenGL/GLShader.h"
#include"Core/Logs/EulerLog.h"
#include"Resource/ResourceLibrary.h"
#include<glm/gtx/quaternion.hpp>
namespace EulerEngine {
	Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();
	void Renderer::Init()
	{
		RenderCommand::Init();

		m_SceneData->CircleShader = ResourceLibrary::LoadShaderInner("Camera/circle.glsl");
		m_SceneData->LineShader = ResourceLibrary::LoadShaderInner("Camera/line.glsl");

		if (false){
			m_SceneData->Cube_VA = EulerEngine::VertexArray::Create();
			m_SceneData->Cube_VB = EulerEngine::VertexBuffer::Create(m_SceneData->MaxVertices * sizeof(EulerEngine::CubeVertex));
			EulerEngine::BufferLayout cube_layout = {
				{EulerEngine::ShaderDataType::Float3, "aPosition"},
				{EulerEngine::ShaderDataType::Float2, "aTexCoord"},
				{EulerEngine::ShaderDataType::Int, "aGameObjectID"},
			};
			m_SceneData->Cube_VB->SetLayout(cube_layout);
			m_SceneData->Cube_VA->AddVertexBuffer(m_SceneData->Cube_VB);
			m_SceneData->CubeVertexBase = new EulerEngine::CubeVertex[m_SceneData->MaxVertices];
		}

		unsigned int offset = 0;
		unsigned int SquareIndices[QUAD_INDEX_CNT] = { 0, 1, 2, 2, 3, 0 };
		unsigned int* QuadIndices = new unsigned int[m_SceneData->MaxIndices];
		for (unsigned int i = 0; i < m_SceneData->MaxIndices; i += QUAD_INDEX_CNT) {
			for (unsigned int j = 0; j < QUAD_INDEX_CNT; j++) {
				QuadIndices[i + j] = offset + SquareIndices[j];
			}
			offset += QUAD_VERTEX_CNT;
		}
		EulerEngine::Ref<EulerEngine::IndexBuffer> indexBuffer
			= EulerEngine::IndexBuffer::Create(QuadIndices, m_SceneData->MaxIndices);
		delete[] QuadIndices;

		{
			m_SceneData->Quad_VA = EulerEngine::VertexArray::Create();
			m_SceneData->Quad_VB = EulerEngine::VertexBuffer::Create(m_SceneData->MaxVertices * sizeof(EulerEngine::QuadVertex));
			EulerEngine::BufferLayout quad_layout = {
				{EulerEngine::ShaderDataType::Float3, "aPosition"},
				{EulerEngine::ShaderDataType::Float2, "aTexCoord"},
				{EulerEngine::ShaderDataType::Int, "aGameObjectID"},
			};
			m_SceneData->Quad_VB->SetLayout(quad_layout);
			m_SceneData->Quad_VA->AddVertexBuffer(m_SceneData->Quad_VB);
			m_SceneData->Quad_VA->SetIndexBuffer(indexBuffer);
			m_SceneData->QuadVertexBase = new EulerEngine::QuadVertex[m_SceneData->MaxVertices];
		}

		
		{
			m_SceneData->Circle_VA = EulerEngine::VertexArray::Create();
			m_SceneData->Circle_VB = EulerEngine::VertexBuffer::Create(m_SceneData->MaxVertices * sizeof(EulerEngine::CircleVertex));
			EulerEngine::BufferLayout circle_layout = {
				{EulerEngine::ShaderDataType::Float3, "aPosition"},
				{EulerEngine::ShaderDataType::Float3, "aLocalPosition"},
				{EulerEngine::ShaderDataType::Float4, "aColor"},
				{EulerEngine::ShaderDataType::Float, "aThickness"},
				{EulerEngine::ShaderDataType::Float,"aFade"},
				{EulerEngine::ShaderDataType::Int, "aGameObjectID"},
			};
			m_SceneData->Circle_VB->SetLayout(circle_layout);
			m_SceneData->Circle_VA->AddVertexBuffer(m_SceneData->Circle_VB);
			m_SceneData->Circle_VA->SetIndexBuffer(indexBuffer);
			m_SceneData->CircleVertexBase = new EulerEngine::CircleVertex[m_SceneData->MaxVertices];
		}

		{
			m_SceneData->Line_VA = EulerEngine::VertexArray::Create();
			m_SceneData->Line_VB = EulerEngine::VertexBuffer::Create(m_SceneData->MaxVertices * sizeof(EulerEngine::LineVertex));
			EulerEngine::BufferLayout line_layout = {
				{EulerEngine::ShaderDataType::Float3, "aPosition"},
				{EulerEngine::ShaderDataType::Float4, "aColor"},
				{EulerEngine::ShaderDataType::Int, "aGameObjectID"},
			};
			m_SceneData->Line_VB->SetLayout(line_layout);
			m_SceneData->Line_VA->AddVertexBuffer(m_SceneData->Line_VB);
			m_SceneData->LineVertexBase = new EulerEngine::LineVertex[m_SceneData->MaxVertices];
		}


		for (unsigned int i = 0; i < m_SceneData->TextureSlots.size(); i++) {
			m_SceneData->TextureSlots[i] = 0;
		}
	}
	void Renderer::ShutDown()
	{
		delete[] m_SceneData->CubeVertexBase;
		delete[] m_SceneData->QuadVertexBase;
	}
	void Renderer::BeginScene(const EulerCamera& camera)
	{
		m_SceneData->ViewMatrix = camera.GetViewMatrix();
		m_SceneData->ProjectionMatrix = camera.GetProjectionMatrix();

		m_SceneData->CubeVertexCount = 0;
		m_SceneData->CubeVertexArrayPtr = m_SceneData->CubeVertexBase;
		
		m_SceneData->QuadIndicesCount = 0;
		m_SceneData->QuadVertexArrayPtr = m_SceneData->QuadVertexBase;

		m_SceneData->CircleIndicesCount = 0;
		m_SceneData->CircleVertexArrayPtr = m_SceneData->CircleVertexBase;

		m_SceneData->LineVertexCount = 0;
		m_SceneData->LineVertexArrayPtr = m_SceneData->LineVertexBase;

		m_SceneData->TextureSlotIndex = 0;
	}
	void Renderer::EndScene()
	{
		Flush();
	}
	void Renderer::Flush() {
		if (m_SceneData->CubeVertexCount > 0) {
			unsigned int byte_offset = (unsigned int)((uint8_t*)m_SceneData->CubeVertexArrayPtr - (uint8_t*)m_SceneData->CubeVertexBase);
			m_SceneData->Cube_VB->SetData(m_SceneData->CubeVertexBase, byte_offset);

			for (unsigned int i = 0; i < m_SceneData->TextureSlotIndex; i++) {
				m_SceneData->TextureSlots[i]->Bind(i);
			}

			RenderCommand::Draw(m_SceneData->Cube_VA, m_SceneData->CubeVertexCount);
			m_SceneData->stats.DrawCalls++;
		}
		if (m_SceneData->QuadIndicesCount > 0) {
			unsigned int byte_offset = (unsigned int)((uint8_t*)m_SceneData->QuadVertexArrayPtr - (uint8_t*)m_SceneData->QuadVertexBase);
			m_SceneData->Quad_VB->SetData(m_SceneData->QuadVertexBase, byte_offset);

			for (unsigned int i = 0; i < m_SceneData->TextureSlotIndex; i++) {
				m_SceneData->TextureSlots[i]->Bind(i);
			}
			m_SceneData->QuadShader->Bind();
			RenderCommand::DrawIndexed(m_SceneData->Quad_VA, m_SceneData->QuadIndicesCount);
			m_SceneData->stats.DrawCalls++;
		}
		if (m_SceneData->CircleIndicesCount > 0) {
			unsigned int byte_offset = (unsigned int)((uint8_t*)m_SceneData->CircleVertexArrayPtr - (uint8_t*)m_SceneData->CircleVertexBase);
			m_SceneData->Circle_VB->SetData(m_SceneData->CircleVertexBase, byte_offset);

			m_SceneData->CircleShader->Bind();
			RenderCommand::DrawIndexed(m_SceneData->Circle_VA, m_SceneData->CircleIndicesCount);
			m_SceneData->stats.DrawCalls++;
		}
		if (m_SceneData->LineVertexCount > 0) {
			unsigned int byte_offset = (unsigned int)((uint8_t*)m_SceneData->LineVertexArrayPtr - (uint8_t*)m_SceneData->LineVertexBase);
			m_SceneData->Line_VB->SetData(m_SceneData->LineVertexBase, byte_offset);

			m_SceneData->LineShader->Bind();
			RenderCommand::SetLineWidth(m_SceneData->LineWidth);
			RenderCommand::DrawLines(m_SceneData->Line_VA, m_SceneData->LineVertexCount);
			m_SceneData->stats.DrawCalls++;
		}
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

		for (unsigned int i = 0; i < CUBE_VERTICE_CNT; i++) {
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

		m_SceneData->CubeVertexCount += CUBE_VERTICE_CNT;
		m_SceneData->stats.CubeCount++;
	}

	void Renderer::DrawQuad(const glm::vec2 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<EulerMaterial>& material, int objID)
	{
		DrawQuad({ position.x, position.y, 0.0f }, rotation, scale, material, objID);
	}
	void Renderer::DrawQuad(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<EulerMaterial>& material, int objID)
	{

		auto shader = material->GetShader();
		m_SceneData->QuadShader = shader;
		shader->Bind();
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

		for (unsigned int i = 0; i < QUAD_VERTICE_CNT; i++) {
			unsigned int head_index = QUAD_DATA_SIZE * i;
			glm::vec4 VerticePosition
				= glm::vec4(EulerEngine::QuadVertices[head_index], EulerEngine::QuadVertices[head_index + 1], EulerEngine::QuadVertices[head_index + 2], 1.0f);
			m_SceneData->QuadVertexArrayPtr->Position = model * VerticePosition;
			m_SceneData->QuadVertexArrayPtr->TexCoord = glm::vec2(EulerEngine::QuadVertices[head_index + 3], EulerEngine::QuadVertices[head_index + 4]);
			m_SceneData->QuadVertexArrayPtr->GameObjectID = objID;
			m_SceneData->QuadVertexArrayPtr++;
		}

		shader->SetMat4("view", m_SceneData->ViewMatrix);
		shader->SetMat4("projection", m_SceneData->ProjectionMatrix);
		shader->SetInt("texture_index", textureIndex);
		shader->SetVec4("color", material->GetColor());

		m_SceneData->QuadIndicesCount += QUAD_INDEX_CNT;
		m_SceneData->stats.QuadCount++;
	}

	void Renderer::DrawCircle(const glm::vec2 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color, float thickness, float fade, int objID)
	{
		DrawCircle({ position.x, position.y, 0.0f }, rotation, scale, color, thickness, fade, objID);
	}
	void Renderer::DrawCircle(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color, float thickness, float fade, int objID)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		model *= glm::toMat4(glm::quat(rotation));
		model = glm::scale(model, scale);

		for (unsigned int i = 0; i < QUAD_VERTICE_CNT; i++) {
			unsigned int head_index = QUAD_DATA_SIZE * i;
			glm::vec4 VerticePosition
				= glm::vec4(EulerEngine::QuadVertices[head_index], EulerEngine::QuadVertices[head_index + 1], EulerEngine::QuadVertices[head_index + 2], 1.0f);
			m_SceneData->CircleVertexArrayPtr->Position = model * VerticePosition;
			m_SceneData->CircleVertexArrayPtr->LocalPosition = VerticePosition * 2.0f;
			m_SceneData->CircleVertexArrayPtr->Color = color;
			m_SceneData->CircleVertexArrayPtr->Thickness = thickness;
			m_SceneData->CircleVertexArrayPtr->Fade = fade;
			m_SceneData->CircleVertexArrayPtr->GameObjectID = objID;
			m_SceneData->CircleVertexArrayPtr++;
		}

		m_SceneData->CircleShader->Bind();
		m_SceneData->CircleShader->SetMat4("view", m_SceneData->ViewMatrix);
		m_SceneData->CircleShader->SetMat4("projection", m_SceneData->ProjectionMatrix);

		m_SceneData->CircleIndicesCount += QUAD_INDEX_CNT;
		m_SceneData->stats.CircleCount++;
	}

	void Renderer::DrawLine(const glm::vec3 start, const glm::vec3 end, const glm::vec4 color, int objID)
	{
		m_SceneData->LineVertexArrayPtr->Position = start;
		m_SceneData->LineVertexArrayPtr->Color = color;
		m_SceneData->LineVertexArrayPtr->GameObjectID = objID;
		m_SceneData->LineVertexArrayPtr++;

		m_SceneData->LineVertexArrayPtr->Position = end;
		m_SceneData->LineVertexArrayPtr->Color = color;
		m_SceneData->LineVertexArrayPtr->GameObjectID = objID;
		m_SceneData->LineVertexArrayPtr++;

		m_SceneData->LineShader->Bind();
		m_SceneData->LineShader->SetMat4("view", m_SceneData->ViewMatrix);
		m_SceneData->LineShader->SetMat4("projection", m_SceneData->ProjectionMatrix);

		m_SceneData->LineVertexCount += 2;
		m_SceneData->stats.LineCount++;
	}

	void Renderer::DrawRect(const glm::vec2 position, const glm::vec3 size, const glm::vec4 color, int objID)
	{
		DrawRect({ position.x, position.y, 0.0f }, size, color, objID);
	}

	void Renderer::DrawRect(const glm::vec3 position, const glm::vec3 size, const glm::vec4 color, int objID)
	{
		glm::vec3 p0 = glm::vec3(position.x - size.x / 2.0f, position.y - size.y / 2.0f, position.z);
		glm::vec3 p1 = glm::vec3(position.x + size.x / 2.0f, position.y - size.y / 2.0f, position.z);
		glm::vec3 p2 = glm::vec3(position.x + size.x / 2.0f, position.y + size.y / 2.0f, position.z);
		glm::vec3 p3 = glm::vec3(position.x - size.x / 2.0f, position.y + size.y / 2.0f, position.z);

		DrawLine(p0, p1, color, objID);
		DrawLine(p1, p2, color, objID);
		DrawLine(p2, p3, color, objID);
		DrawLine(p3, p0, color, objID);
	}

	void Renderer::DrawRect(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color, int objID)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		model *= glm::toMat4(glm::quat(rotation));
		model = glm::scale(model, scale);
		glm::vec3 LineVertices[QUAD_VERTICE_CNT];
		glm::vec4 QuadVertices[QUAD_VERTICE_CNT];
		for (unsigned int i = 0; i < QUAD_VERTICE_CNT; i++) {
			unsigned int head_index = QUAD_DATA_SIZE * i;
			glm::vec4 VerticePosition
				= glm::vec4(EulerEngine::QuadVertices[head_index], EulerEngine::QuadVertices[head_index + 1], EulerEngine::QuadVertices[head_index + 2], 1.0f);
			QuadVertices[i] = VerticePosition;
		}

		for (unsigned int i = 0; i < QUAD_VERTICE_CNT; i++) {
			LineVertices[i] = model * QuadVertices[i];
		}
		DrawLine(LineVertices[0], LineVertices[1], color);
		DrawLine(LineVertices[1], LineVertices[2], color);
		DrawLine(LineVertices[2], LineVertices[3], color);
		DrawLine(LineVertices[3], LineVertices[0], color);
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
		const glm::mat4& model, const unsigned int vertex_cnt)
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