#include"gkpch.h"
#include"EulerBatch.h"
#include"Render/RawData/EulerMesh.h"
#include"Render/RawData/EulerVertices.h"
#include"Resource/ResourceLibrary.h"
#define QUAD_VERTEX_CNT 4
#define CUBE_VERTEX_CNT 8
#define QUAD_INDEX_CNT 6
#define CUBE_INDEX_CNT 24
namespace EulerEngine {
	Scope<EulerBatch::CubeBatchData> EulerBatch::s_CubeData = CreateScope<EulerBatch::CubeBatchData>();
	Scope<EulerBatch::QuadBatchData> EulerBatch::s_QuadData = CreateScope<EulerBatch::QuadBatchData>();
	Scope<EulerBatch::LineBatchData> EulerBatch::s_LineData = CreateScope<EulerBatch::LineBatchData>();
	void EulerBatch::Init()
	{
		s_LineData->Shader = ResourceLibrary::LoadShaderInner("Camera/line.glsl");
		InitCubeData();
		InitQuadData();
		InitLineData();
	}
	void EulerBatch::Shutdown()
	{
		delete[] s_CubeData->VertexBase;
		delete[] s_QuadData->VertexBase;
		delete[] s_LineData->VertexBase;
	}
	void EulerBatch::SubmitCube(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial>& material, int objID)
	{
		auto shader = material->GetShader();
		s_CubeData->Shader = shader; //this should be an buffer if we want to use multiple shaders
		int samplers[MAX_TEXTURE_SLOTS];
		for (unsigned int i = 0; i < MAX_TEXTURE_SLOTS; i++) {
			samplers[i] = i;
		}
		shader->SetIntArray("sampler2D", samplers, MAX_TEXTURE_SLOTS);

		auto texture = material->GetTexture();
		float textureIndex = 0.0f;
		if (texture != nullptr) {
			for (unsigned int i = 1; i < s_CubeData->Texture2DSlotLoadedCount; i++) {
				if (*s_CubeData->Texture2DSlots[i] == *texture) {
					textureIndex = (float)i;
					break;
				}
			}

			if (textureIndex == 0.0f) {
				textureIndex = (float)s_CubeData->Texture2DSlotLoadedCount;
				s_CubeData->Texture2DSlots[s_CubeData->Texture2DSlotLoadedCount++] = texture;
			}
		}
		else {
			textureIndex = -1.0f;
			KINK_CORE_WARN("No texture found for cube");
		}

		shader->Bind();
		shader->SetMat4("view", view);
		shader->SetMat4("projection", projection);
		shader->SetInt("texture_index", textureIndex);

		std::vector<float> vertices = mesh->GetVertices();
		if (s_CubeData->SingleIndices.size() == 0) {
			s_CubeData->SingleIndices = mesh->GetIndices();
		}
		for (unsigned int i = 0; i < CUBE_VERTICE_CNT; i++) {
			unsigned int head_index = CUBE_DATA_SIZE * i;
			s_CubeData->VertexArrayPtr->Position = model * glm::vec4(vertices[head_index], vertices[head_index + 1], vertices[head_index + 2], 1.0f);
			s_CubeData->VertexArrayPtr->TexCoord = glm::vec2(vertices[head_index + 3], vertices[head_index + 4]);
			s_CubeData->VertexArrayPtr->Normal = glm::vec3(vertices[head_index + 5], vertices[head_index + 6], vertices[head_index + 7]);
			s_CubeData->VertexArrayPtr->GameObjectID = objID;
			s_CubeData->VertexArrayPtr++;
		}
		s_CubeData->VertexCount += CUBE_VERTEX_CNT;
	}
	void EulerBatch::SubmitSphere(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial>& material, const int objID)
	{
	}
	void EulerBatch::SubmitQuad(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial2D>& material, const int objID)
	{
		auto shader = material->GetShader();
		s_QuadData->Shader = shader;
		shader->Bind();
		int samplers[MAX_TEXTURE_SLOTS];
		for (unsigned int i = 0; i < MAX_TEXTURE_SLOTS; i++) {
			samplers[i] = i;
		}
		shader->SetIntArray("sampler2D", samplers, MAX_TEXTURE_SLOTS);

		auto texture = material->GetTexture();
		float textureIndex = 0.0f;
		if (texture != nullptr) {
			for (unsigned int i = 1; i < s_QuadData->Texture2DSlotLoadedCount; i++) {
				if (*s_QuadData->Texture2DSlots[i] == *texture) {
					textureIndex = (float)i;
					break;
				}
			}
			if (textureIndex == 0.0f) {
				textureIndex = (float)s_QuadData->Texture2DSlotLoadedCount;
				s_QuadData->Texture2DSlots[s_QuadData->Texture2DSlotLoadedCount++] = texture;
			}
		}
		else {
			textureIndex = -1.0f;
			KINK_CORE_WARN("No texture found for quad");
		}

		shader->SetMat4("view", view);
		shader->SetMat4("projection", projection);
		shader->SetInt("texture_index", textureIndex);

		std::vector<float> vertices = mesh->GetVertices();
		if (s_QuadData->SingleIndices.size() == 0) {
			s_QuadData->SingleIndices = mesh->GetIndices();
		}
		for (unsigned int i = 0; i < QUAD_VERTICE_CNT; i++) {
			unsigned int head_index = QUAD_DATA_SIZE * i;
			s_QuadData->VertexArrayPtr->Position = model * glm::vec4(vertices[head_index], vertices[head_index + 1], vertices[head_index + 2], 1.0f);
			s_QuadData->VertexArrayPtr->TexCoord = glm::vec2(vertices[head_index + 3], vertices[head_index + 4]);
			s_QuadData->VertexArrayPtr->Color = material->GetColor();
			s_QuadData->VertexArrayPtr->GameObjectID = objID;
			s_QuadData->VertexArrayPtr++;
		}
		s_QuadData->IndexCount += QUAD_INDEX_CNT;
	}
	void EulerBatch::SubmitModel(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial>& material, const int objID)
	{

	}
	void EulerBatch::SubmitLine(const glm::mat4& view, const glm::mat4& projection, const const glm::vec3 start, const glm::vec3 end, const glm::vec4 color, const int objID)
	{
		s_LineData->VertexArrayPtr->Position = start;
		s_LineData->VertexArrayPtr->Color = color;
		s_LineData->VertexArrayPtr->GameObjectID = objID;
		s_LineData->VertexArrayPtr++;
		s_LineData->VertexArrayPtr->Position = end;
		s_LineData->VertexArrayPtr->Color = color;
		s_LineData->VertexArrayPtr->GameObjectID = objID;
		s_LineData->VertexArrayPtr++;
		s_LineData->VertexCount += LINE_VERTEX_CNT;
		s_LineData->Shader->Bind();
		s_LineData->Shader->SetMat4("view", view);
		s_LineData->Shader->SetMat4("projection", projection);
	}
	void EulerBatch::Clear()
	{
		s_CubeData->VertexArrayPtr = s_CubeData->VertexBase;
		s_QuadData->VertexArrayPtr = s_QuadData->VertexBase;
		s_LineData->VertexArrayPtr = s_LineData->VertexBase;
		s_QuadData->Texture2DSlotLoadedCount = 0;
		s_CubeData->Texture2DSlotLoadedCount = 0;
		s_LineData->VertexCount = 0;
		s_QuadData->IndexCount = 0;
		s_CubeData->VertexCount = 0;
	}
	unsigned int EulerBatch::Flush()
	{
		unsigned int draw_call_count = 0;
		if (s_CubeData->VertexArrayPtr != s_CubeData->VertexBase) {
			unsigned int byte_offset = (unsigned int)((uint8_t*)s_CubeData->VertexArrayPtr - (uint8_t*)s_CubeData->VertexBase);
			s_CubeData->VB->SetData(s_CubeData->VertexBase, byte_offset);

			unsigned int* indices = Generator::GenerateCubeIndices(s_CubeData->SingleIndices, s_CubeData->MaxIndices);
			s_QuadData->IB->SetData(indices, s_CubeData->MaxIndices);

			for (unsigned int i = 0; i < s_CubeData->Texture2DSlotLoadedCount; i++) {
				s_CubeData->Texture2DSlots[i]->Bind(i);
			}
			s_CubeData->Shader->Bind();
			RenderCommand::Draw(s_CubeData->VA, s_CubeData->VertexCount);
			draw_call_count++;
		}

		if (s_QuadData->VertexArrayPtr != s_QuadData->VertexBase) {
			unsigned int byte_offset = (unsigned int)((uint8_t*)s_QuadData->VertexArrayPtr - (uint8_t*)s_QuadData->VertexBase);
			s_QuadData->VB->SetData(s_QuadData->VertexBase, byte_offset);

			unsigned int* indices = Generator::GenerateQuadIndices(s_QuadData->SingleIndices, s_QuadData->IndexCount);
			s_QuadData->IB->SetData(indices, s_QuadData->IndexCount);

			for (unsigned int i = 0; i < s_QuadData->Texture2DSlotLoadedCount; i++) {
				s_QuadData->Texture2DSlots[i]->Bind(i);
			}
			s_QuadData->Shader->Bind();
			RenderCommand::DrawIndexed(s_QuadData->VA, s_QuadData->IndexCount);
			draw_call_count++;
		}

		if (s_LineData->VertexArrayPtr != s_LineData->VertexBase) {
			unsigned int byte_offset = (unsigned int)((uint8_t*)s_LineData->VertexArrayPtr - (uint8_t*)s_LineData->VertexBase);
			s_LineData->VB->SetData(s_LineData->VertexBase, byte_offset);

			s_LineData->Shader->Bind();
			RenderCommand::SetLineWidth(s_LineData->LineWidth);
			RenderCommand::DrawLines(s_LineData->VA, s_LineData->VertexCount);
			draw_call_count++;
		}
		return draw_call_count;
	}
	void EulerBatch::InitCubeData()
	{
		s_CubeData->VA = VertexArray::Create();
		s_CubeData->VB = VertexBuffer::Create(s_CubeData->MaxVertices * sizeof(Vertex));
		s_CubeData->IB = IndexBuffer::Create(s_CubeData->MaxIndices);
		BufferLayout cube_layout = {
			{ShaderDataType::Float3, "aPosition"},
			{ShaderDataType::Float2, "aTexCoord"},
			{ShaderDataType::Float3, "aNormal"},
			{ShaderDataType::Int, "aGameObjectID"},
		};
		s_CubeData->VB->SetLayout(cube_layout);
		s_CubeData->VA->AddVertexBuffer(s_CubeData->VB);
		s_CubeData->VA->SetIndexBuffer(s_CubeData->IB);
		s_CubeData->VertexBase = new Vertex[s_CubeData->MaxVertices];

		for (unsigned int i = 0; i < MAX_TEXTURE_SLOTS; i++) {
			s_CubeData->Texture2DSlots[i] = 0;
		}
	}
	void EulerBatch::InitQuadData()
	{

		s_QuadData->VA = VertexArray::Create();
		s_QuadData->VB = VertexBuffer::Create(s_QuadData->MaxVertices * sizeof(SpriteVertex));
		s_QuadData->IB = IndexBuffer::Create(s_QuadData->MaxIndices);
		BufferLayout quad_layout = {
			{ShaderDataType::Float3, "aPosition"},
			{ShaderDataType::Float2, "aTexCoord"},
			{ShaderDataType::Float4, "aColor"},
			{ShaderDataType::Int, "aGameObjectID"},
		};
		s_QuadData->VB->SetLayout(quad_layout);
		s_QuadData->VA->AddVertexBuffer(s_QuadData->VB);
		s_QuadData->VA->SetIndexBuffer(s_QuadData->IB);
		s_QuadData->VertexBase = new SpriteVertex[s_QuadData->MaxVertices];

		for (unsigned int i = 0; i < MAX_TEXTURE_SLOTS; i++) {
			s_QuadData->Texture2DSlots[i] = 0;
		}
	}
	void EulerBatch::InitLineData()
	{
		s_LineData->VA = VertexArray::Create();
		s_LineData->VB = VertexBuffer::Create(s_LineData->MaxVertices * sizeof(LineVertex));
		BufferLayout line_layout = {
			{ShaderDataType::Float3, "aPosition"},
			{ShaderDataType::Float4, "aColor"},
			{ShaderDataType::Int, "aGameObjectID"},
		};
		s_LineData->VB->SetLayout(line_layout);
		s_LineData->VA->AddVertexBuffer(s_LineData->VB);
		s_LineData->VertexBase = new LineVertex[s_LineData->MaxVertices];
	}
}