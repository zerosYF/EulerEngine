#include"gkpch.h"
#include"EulerBatch.h"
#include"Render/RawData/EulerMesh.h"
#include"Resource/ResourceLibrary.h"
namespace EulerEngine {
	Scope<EulerBatch::CubeBatchData> EulerBatch::s_CubeData = CreateScope<EulerBatch::CubeBatchData>();
	Scope<EulerBatch::PlaneBatchData> EulerBatch::s_PlaneData = CreateScope<EulerBatch::PlaneBatchData>();
	Scope<EulerBatch::SpriteBatchData> EulerBatch::s_SpriteData = CreateScope<EulerBatch::SpriteBatchData>();
	Scope<EulerBatch::LineBatchData> EulerBatch::s_LineData = CreateScope<EulerBatch::LineBatchData>();
	void EulerBatch::Init()
	{
		s_LineData->Shader = ResourceLibrary::LoadShaderInner("line.glsl");
		InitCubeData();
		InitPlaneData();
		InitSpriteData();
		InitLineData();
	}
	void EulerBatch::Shutdown()
	{
		delete[] s_CubeData->VertexBase;
		delete[] s_PlaneData->VertexBase;
		delete[] s_SpriteData->VertexBase;
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
		int textureIndex = -1;
		if (texture != nullptr) {
			for (unsigned int i = 0; i < s_CubeData->Texture2DSlotLoadedCount; i++) {
				if (*s_CubeData->Texture2DSlots[i] == *texture) {
					textureIndex = i;
					break;
				}
			}

			if (textureIndex == -1) {
				textureIndex = s_CubeData->Texture2DSlotLoadedCount;
				s_CubeData->Texture2DSlots[s_CubeData->Texture2DSlotLoadedCount++] = texture;
			}
		}
		else {
			textureIndex = -1;
			KINK_CORE_WARN("No texture found for cube");
		}

		shader->Bind();
		shader->SetMat4("view", view);
		shader->SetMat4("projection", projection);
		shader->SetInt("texture_index", textureIndex);

		std::vector<float> vertices = mesh->GetVertices();
		s_CubeData->SingleIndices = mesh->GetIndices();
		for (unsigned int i = 0; i < CUBE_VERTEX_CNT; i++) {
			unsigned int head_index = CUBE_DATA_SIZE * i;
			s_CubeData->VertexArrayPtr->Position = model * glm::vec4(vertices[head_index], vertices[head_index + 1], vertices[head_index + 2], 1.0f);
			s_CubeData->VertexArrayPtr->TexCoord = glm::vec2(vertices[head_index + 3], vertices[head_index + 4]);
			s_CubeData->VertexArrayPtr->Normal = model *glm::vec4(vertices[head_index + 5], vertices[head_index + 6], vertices[head_index + 7], 0.0f);
			s_CubeData->VertexArrayPtr->GameObjectID = objID;
			s_CubeData->VertexArrayPtr++;
		}
		s_CubeData->VertexCount += CUBE_VERTEX_CNT;
		s_CubeData->IndexCount += CUBE_INDEX_CNT;
	}
	void EulerBatch::SubmitSphere(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial>& material, const int objID)
	{
	}
	void EulerBatch::SubmitPlane(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial>& material, const int objID) {
		auto shader = material->GetShader();
		s_PlaneData->Shader = shader;
		shader->Bind();
		int samplers[MAX_TEXTURE_SLOTS];
		for (unsigned int i = 0; i < MAX_TEXTURE_SLOTS; i++) {
			samplers[i] = i;
		}
		shader->SetIntArray("sampler2D", samplers, MAX_TEXTURE_SLOTS);

		auto texture = material->GetTexture();
		int textureIndex = -1;
		if (texture != nullptr) {
			for (unsigned int i = 0; i < s_PlaneData->Texture2DSlotLoadedCount; i++) {
				if (*s_PlaneData->Texture2DSlots[i] == *texture) {
					textureIndex = i;
					break;
				}
			}
			if (textureIndex == -1) {
				textureIndex = s_PlaneData->Texture2DSlotLoadedCount;
				s_PlaneData->Texture2DSlots[s_PlaneData->Texture2DSlotLoadedCount++] = texture;
			}
		}
		else {
			textureIndex = -1;
			KINK_CORE_WARN("No texture found for plane");
		}

		shader->SetMat4("view", view);
		shader->SetMat4("projection", projection);
		shader->SetInt("texture_index", textureIndex);

		std::vector<float> vertices = mesh->GetVertices();
		s_PlaneData->SingleIndices = mesh->GetIndices();
		for (unsigned int i = 0; i < PLANE_VERTEX_CNT; i++) {
			unsigned int head_index = PLANE_DATA_SIZE * i;
			s_PlaneData->VertexArrayPtr->Position = model * glm::vec4(vertices[head_index], vertices[head_index + 1], vertices[head_index + 2], 1.0f);
			s_PlaneData->VertexArrayPtr->TexCoord = glm::vec2(vertices[head_index + 3], vertices[head_index + 4]);
			s_PlaneData->VertexArrayPtr->Normal = model * glm::vec4(vertices[head_index + 5], vertices[head_index + 6], vertices[head_index + 7], 0.0f);
			s_PlaneData->VertexArrayPtr->GameObjectID = objID;
			s_PlaneData->VertexArrayPtr++;
		}
		s_PlaneData->VertexCount += PLANE_VERTEX_CNT;
		s_PlaneData->IndexCount += PLANE_INDEX_CNT;
	}
	void EulerBatch::SubmitSprite(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial2D>& material, const int objID)
	{
		auto shader = material->GetShader();
		s_SpriteData->Shader = shader;
		shader->Bind();
		int samplers[MAX_TEXTURE_SLOTS];
		for (unsigned int i = 0; i < MAX_TEXTURE_SLOTS; i++) {
			samplers[i] = i;
		}
		shader->SetIntArray("sampler2D", samplers, MAX_TEXTURE_SLOTS);

		auto texture = material->GetTexture();
		int textureIndex = -1;
		if (texture != nullptr) {
			for (unsigned int i = 0; i < s_SpriteData->Texture2DSlotLoadedCount; i++) {
				if (*s_SpriteData->Texture2DSlots[i] == *texture) {
					textureIndex = i;
					break;
				}
			}
			if (textureIndex == -1) {
				textureIndex = s_SpriteData->Texture2DSlotLoadedCount;
				s_SpriteData->Texture2DSlots[s_SpriteData->Texture2DSlotLoadedCount++] = texture;
			}
		}
		else {
			textureIndex = -1;
			KINK_CORE_WARN("No texture found for sprite");
		}

		shader->SetMat4("view", view);
		shader->SetMat4("projection", projection);
		shader->SetInt("texture_index", textureIndex);

		std::vector<float> vertices = mesh->GetVertices();
		s_SpriteData->SingleIndices = mesh->GetIndices();
		for (unsigned int i = 0; i < SPRITE_VERTEX_CNT; i++) {
			unsigned int head_index = SPRITE_DATA_SIZE * i;
			s_SpriteData->VertexArrayPtr->Position = model * glm::vec4(vertices[head_index], vertices[head_index + 1], vertices[head_index + 2], 1.0f);
			s_SpriteData->VertexArrayPtr->TexCoord = glm::vec2(vertices[head_index + 3], vertices[head_index + 4]);
			s_SpriteData->VertexArrayPtr->Color = material->GetColor();
			s_SpriteData->VertexArrayPtr->GameObjectID = objID;
			s_SpriteData->VertexArrayPtr++;
		}
		s_SpriteData->VertexCount += SPRITE_VERTEX_CNT;
		s_SpriteData->IndexCount += SPRITE_INDEX_CNT;
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
		s_CubeData->VertexCount = 0;
		s_CubeData->IndexCount = 0;
		s_CubeData->VertexArrayPtr = s_CubeData->VertexBase;

		s_PlaneData->VertexCount = 0;
		s_PlaneData->IndexCount = 0;
		s_PlaneData->VertexArrayPtr = s_PlaneData->VertexBase;

		s_SpriteData->VertexCount = 0;
		s_SpriteData->IndexCount = 0;
		s_SpriteData->VertexArrayPtr = s_SpriteData->VertexBase;

		s_LineData->VertexCount = 0;
		s_LineData->VertexArrayPtr = s_LineData->VertexBase;

		s_SpriteData->Texture2DSlotLoadedCount = 0;
		s_CubeData->Texture2DSlotLoadedCount = 0;
		s_PlaneData->Texture2DSlotLoadedCount = 0;
	}
	unsigned int EulerBatch::Flush()
	{
		unsigned int draw_call_count = 0;
		draw_call_count += FlushCubeData();
		draw_call_count += FlushPlaneData();
		draw_call_count += FlushSpriteData();
		draw_call_count += FlushLineData();
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
	void EulerBatch::InitPlaneData()
	{
		s_PlaneData->VA = VertexArray::Create();
		s_PlaneData->VB = VertexBuffer::Create(s_PlaneData->MaxVertices * sizeof(Vertex));
		s_PlaneData->IB = IndexBuffer::Create(s_PlaneData->MaxIndices);
		BufferLayout plane_layout = {
			{ShaderDataType::Float3, "aPosition"},
			{ShaderDataType::Float2, "aTexCoord"},
			{ShaderDataType::Float3, "aNormal"},
			{ShaderDataType::Int, "aGameObjectID"},
		};
		s_PlaneData->VB->SetLayout(plane_layout);
		s_PlaneData->VA->AddVertexBuffer(s_PlaneData->VB);
		s_PlaneData->VA->SetIndexBuffer(s_PlaneData->IB);
		s_PlaneData->VertexBase = new Vertex[s_PlaneData->MaxVertices];

		for (unsigned int i = 0; i < MAX_TEXTURE_SLOTS; i++) {
			s_PlaneData->Texture2DSlots[i] = 0;
		}
	}
	void EulerBatch::InitSpriteData()
	{

		s_SpriteData->VA = VertexArray::Create();
		s_SpriteData->VB = VertexBuffer::Create(s_SpriteData->MaxVertices * sizeof(SpriteVertex));
		s_SpriteData->IB = IndexBuffer::Create(s_SpriteData->MaxIndices);
		BufferLayout quad_layout = {
			{ShaderDataType::Float3, "aPosition"},
			{ShaderDataType::Float2, "aTexCoord"},
			{ShaderDataType::Float4, "aColor"},
			{ShaderDataType::Int, "aGameObjectID"},
		};
		s_SpriteData->VB->SetLayout(quad_layout);
		s_SpriteData->VA->AddVertexBuffer(s_SpriteData->VB);
		s_SpriteData->VA->SetIndexBuffer(s_SpriteData->IB);
		s_SpriteData->VertexBase = new SpriteVertex[s_SpriteData->MaxVertices];

		for (unsigned int i = 0; i < MAX_TEXTURE_SLOTS; i++) {
			s_SpriteData->Texture2DSlots[i] = 0;
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
	unsigned int EulerBatch::FlushCubeData()
	{
		if (s_CubeData->VertexArrayPtr != s_CubeData->VertexBase) {
			unsigned int byte_offset = (unsigned int)((uint8_t*)s_CubeData->VertexArrayPtr - (uint8_t*)s_CubeData->VertexBase);
			s_CubeData->VB->SetData(s_CubeData->VertexBase, byte_offset);

			unsigned int* indices = Generator::GenerateIndices(s_CubeData->SingleIndices, s_CubeData->IndexCount, CUBE_VERTEX_CNT);
			s_CubeData->IB->SetData(indices, s_CubeData->IndexCount);

			for (unsigned int i = 0; i < s_CubeData->Texture2DSlotLoadedCount; i++) {
				s_CubeData->Texture2DSlots[i]->Bind(i);
			}
			s_CubeData->Shader->Bind();
			RenderCommand::Draw(s_CubeData->VA, s_CubeData->VertexCount);
			return 1;
		}
		return 0;
	}
	unsigned int EulerBatch::FlushPlaneData()
	{
		if (s_PlaneData->VertexArrayPtr != s_PlaneData->VertexBase) {
			unsigned int byte_offset = (unsigned int)((uint8_t*)s_PlaneData->VertexArrayPtr - (uint8_t*)s_PlaneData->VertexBase);
			s_PlaneData->VB->SetData(s_PlaneData->VertexBase, byte_offset);

			unsigned int* indices = Generator::GenerateIndices(s_PlaneData->SingleIndices, s_PlaneData->IndexCount, PLANE_VERTEX_CNT);
			s_PlaneData->IB->SetData(indices, s_PlaneData->IndexCount);

			for (unsigned int i = 0; i < s_PlaneData->Texture2DSlotLoadedCount; i++) {
				s_PlaneData->Texture2DSlots[i]->Bind(i);
			}
			s_PlaneData->Shader->Bind();
			RenderCommand::DrawIndexed(s_PlaneData->VA, s_PlaneData->IndexCount);
			return 1;
		}
		return 0;
	}
	unsigned int EulerBatch::FlushSpriteData()
	{
		if (s_SpriteData->VertexArrayPtr != s_SpriteData->VertexBase) {
			unsigned int byte_offset = (unsigned int)((uint8_t*)s_SpriteData->VertexArrayPtr - (uint8_t*)s_SpriteData->VertexBase);
			s_SpriteData->VB->SetData(s_SpriteData->VertexBase, byte_offset);

			unsigned int* indices = Generator::GenerateIndices(s_SpriteData->SingleIndices, s_SpriteData->IndexCount, SPRITE_VERTEX_CNT);
			s_SpriteData->IB->SetData(indices, s_SpriteData->IndexCount);

			for (unsigned int i = 0; i < s_SpriteData->Texture2DSlotLoadedCount; i++) {
				s_SpriteData->Texture2DSlots[i]->Bind(i);
			}
			s_SpriteData->Shader->Bind();
			RenderCommand::DrawIndexed(s_SpriteData->VA, s_SpriteData->IndexCount);
			return 1;
		}
		return 0;
	}
	unsigned int EulerBatch::FlushLineData()
	{
		if (s_LineData->VertexArrayPtr != s_LineData->VertexBase) {
			unsigned int byte_offset = (unsigned int)((uint8_t*)s_LineData->VertexArrayPtr - (uint8_t*)s_LineData->VertexBase);
			s_LineData->VB->SetData(s_LineData->VertexBase, byte_offset);

			s_LineData->Shader->Bind();
			RenderCommand::SetLineWidth(s_LineData->LineWidth);
			RenderCommand::DrawLines(s_LineData->VA, s_LineData->VertexCount);
			return 1;
		}
		return 0;
	}
}