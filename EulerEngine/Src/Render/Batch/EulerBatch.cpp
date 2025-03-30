#include"gkpch.h"
#include"EulerBatch.h"
#include"Render/RawData/EulerMesh.h"
#include"Resource/ResourceLibrary.h"
namespace EulerEngine {
	static BatchData<SpriteVertex> s_SpriteData;
	static BatchData<NormalVertex> s_CubeData;
	static BatchData<NormalVertex> s_PlaneData;
	static BatchData<LineVertex> s_LineData;
	void EulerBatch::Init()
	{
		s_CubeData.BatchInit(MAX_CUBE_COUNT, CUBE_VERTEX_CNT);
		s_PlaneData.BatchInit(MAX_PLANE_COUNT, PLANE_VERTEX_CNT);
		s_PlaneData.SetIndexBuffer(PlaneIndices, PLANE_INDEX_CNT);
		s_SpriteData.BatchInit(MAX_SPRITE_COUNT, SPRITE_VERTEX_CNT);
		s_SpriteData.SetIndexBuffer(SpriteIndices, SPRITE_INDEX_CNT);
		s_LineData.BatchInit(MAX_LINE_COUNT, LINE_VERTEX_CNT);
		auto line_shader = ResourceLibrary::LoadShaderInner("line.glsl");
		s_LineData.SetShader(line_shader);
	}
	void EulerBatch::Shutdown()
	{
		s_CubeData.BatchShutdown();
		s_PlaneData.BatchShutdown();
		s_SpriteData.BatchShutdown();
		s_LineData.BatchShutdown();
	}
	void EulerBatch::SubmitCube(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial3D>& material, int objID)
	{
		s_CubeData.SetShader(material->GetShader());
		int samplers[MAX_TEXTURE_SLOTS];
		for (unsigned int i = 0; i < MAX_TEXTURE_SLOTS; i++) {
			samplers[i] = i;
		}
		s_CubeData.GetShader()->SetIntArray("sampler2D", samplers, MAX_TEXTURE_SLOTS);
		s_CubeData.BatchApplyUniforms(view, projection, material);
		std::vector<float> vertices = mesh->GetVertices();
		for (unsigned int i = 0; i < CUBE_VERTEX_CNT; i++) {
			unsigned int head_index = CUBE_DATA_SIZE * i;
			s_CubeData.m_VertexArrayPtr->Position = model * glm::vec4(vertices[head_index], vertices[head_index + 1], vertices[head_index + 2], 1.0f);
			s_CubeData.m_VertexArrayPtr->TexCoord = glm::vec2(vertices[head_index + 3], vertices[head_index + 4]);
			s_CubeData.m_VertexArrayPtr->Normal = model *glm::vec4(vertices[head_index + 5], vertices[head_index + 6], vertices[head_index + 7], 0.0f);
			s_CubeData.m_VertexArrayPtr->GameObjectID = objID;
			s_CubeData.m_VertexArrayPtr++;
		}
		s_CubeData.m_VertexCount += CUBE_VERTEX_CNT;
	}
	void EulerBatch::SubmitSphere(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial3D>& material, const int objID)
	{
	}
	void EulerBatch::SubmitPlane(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial3D>& material, const int objID) {
		
		s_PlaneData.SetShader(material->GetShader());
		int samplers[MAX_TEXTURE_SLOTS];
		for (unsigned int i = 0; i < MAX_TEXTURE_SLOTS; i++) {
			samplers[i] = i;
		}
		s_PlaneData.GetShader()->SetIntArray("sampler2D", samplers, MAX_TEXTURE_SLOTS);
		s_PlaneData.BatchApplyUniforms(view, projection, material);
		std::vector<float> vertices = mesh->GetVertices();
		for (unsigned int i = 0; i < PLANE_VERTEX_CNT; i++) {
			unsigned int head_index = PLANE_DATA_SIZE * i;
			s_PlaneData.m_VertexArrayPtr->Position = model * glm::vec4(vertices[head_index], vertices[head_index + 1], vertices[head_index + 2], 1.0f);
			s_PlaneData.m_VertexArrayPtr->TexCoord = glm::vec2(vertices[head_index + 3], vertices[head_index + 4]);
			s_PlaneData.m_VertexArrayPtr->Normal = model * glm::vec4(vertices[head_index + 5], vertices[head_index + 6], vertices[head_index + 7], 0.0f);
			s_PlaneData.m_VertexArrayPtr->GameObjectID = objID;
			s_PlaneData.m_VertexArrayPtr++;
		}
		s_PlaneData.m_VertexCount += PLANE_VERTEX_CNT;
		s_PlaneData.m_IndexCount += PLANE_INDEX_CNT;
	}
	void EulerBatch::SubmitSprite(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial2D>& material, const int objID)
	{
		s_SpriteData.SetShader(material->GetShader());
		int samplers[MAX_TEXTURE_SLOTS];
		for (unsigned int i = 0; i < MAX_TEXTURE_SLOTS; i++) {
			samplers[i] = i;
		}
		s_SpriteData.GetShader()->SetIntArray("sampler2D", samplers, MAX_TEXTURE_SLOTS);
		s_SpriteData.BatchApplyUniforms(view, projection, material);
		std::vector<float> vertices = mesh->GetVertices();
		for (unsigned int i = 0; i < SPRITE_VERTEX_CNT; i++) {
			unsigned int head_index = SPRITE_DATA_SIZE * i;
			s_SpriteData.m_VertexArrayPtr->Position = model * glm::vec4(vertices[head_index], vertices[head_index + 1], vertices[head_index + 2], 1.0f);
			s_SpriteData.m_VertexArrayPtr->TexCoord = glm::vec2(vertices[head_index + 3], vertices[head_index + 4]);
			s_SpriteData.m_VertexArrayPtr->Color = material->GetColor();
			s_SpriteData.m_VertexArrayPtr->GameObjectID = objID;
			s_SpriteData.m_VertexArrayPtr++;
		}
		s_SpriteData.m_VertexCount += SPRITE_VERTEX_CNT;
		s_SpriteData.m_IndexCount += SPRITE_INDEX_CNT;
	}
	void EulerBatch::SubmitModel(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial3D>& material, const int objID)
	{

	}
	void EulerBatch::SubmitLine(const glm::mat4& view, const glm::mat4& projection, const const glm::vec3 start, const glm::vec3 end, const glm::vec4 color, const int objID)
	{
		s_LineData.m_VertexArrayPtr->Position = start;
		s_LineData.m_VertexArrayPtr->Color = color;
		s_LineData.m_VertexArrayPtr->GameObjectID = objID;
		s_LineData.m_VertexArrayPtr++;
		s_LineData.m_VertexArrayPtr->Position = end;
		s_LineData.m_VertexArrayPtr->Color = color;
		s_LineData.m_VertexArrayPtr->GameObjectID = objID;
		s_LineData.m_VertexArrayPtr++;
		s_LineData.m_VertexCount += LINE_VERTEX_CNT;
		s_LineData.GetShader()->Bind();
		s_LineData.GetShader()->SetMat4("view", view);
		s_LineData.GetShader()->SetMat4("projection", projection);
	}
	void EulerBatch::Clear()
	{
		s_CubeData.BatchClear();
		s_PlaneData.BatchClear();
		s_SpriteData.BatchClear();
		s_LineData.BatchClear();

	}
	unsigned int EulerBatch::Flush()
	{
		unsigned int draw_call_count = 0;
		draw_call_count += s_SpriteData.BatchFlush();
		draw_call_count += s_CubeData.BatchFlush();
		draw_call_count += s_PlaneData.BatchFlush();
		draw_call_count += s_LineData.BatchFlush();
		return draw_call_count;
	}
}