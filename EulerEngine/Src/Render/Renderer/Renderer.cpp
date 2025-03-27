#include"gkpch.h"
#include"Renderer.h"
#include"RenderCmd.h"
#include"Platform/OpenGL/GLShader.h"
#include"Core/Logs/EulerLog.h"
#include"Resource/ResourceLibrary.h"
#include<glm/gtx/quaternion.hpp>
namespace EulerEngine {
	Scope<Renderer::RenderData> Renderer::s_RenderData = CreateScope<Renderer::RenderData>();
	void Renderer::Init()
	{
		RenderCommand::Init();
		EulerBatch::Init();
	}
	void Renderer::ShutDown()
	{
		EulerBatch::Shutdown();
	}
	void Renderer::BeginScene(const EulerCamera& camera)
	{
		s_RenderData->ViewMatrix = camera.GetViewMatrix();
		s_RenderData->ProjectionMatrix = camera.GetProjectionMatrix();
		EulerBatch::Clear();
	}
	void Renderer::EndScene()
	{  
		s_RenderData->Stats.DrawCalls += EulerBatch::Flush();
	}

	void Renderer::DrawCube(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial>& material, int objID)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		model *= glm::toMat4(glm::quat(rotation));
		model = glm::scale(model, scale);
		EulerBatch::SubmitCube(model, s_RenderData->ViewMatrix, s_RenderData->ProjectionMatrix, mesh, material, objID);
		s_RenderData->Stats.CubeCount++;
	}
	void Renderer::DrawSprite(const glm::vec2 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial2D>& material, int objID)
	{
		DrawSprite({ position.x, position.y, 0.0f }, rotation, scale, mesh, material, objID);
	}
	void Renderer::DrawSprite(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const Ref<EulerMesh>& mesh, const Ref<EulerMaterial2D>& material, int objID)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		model *= glm::toMat4(glm::quat(rotation));
		model = glm::scale(model, scale);
		EulerBatch::SubmitQuad(model, s_RenderData->ViewMatrix, s_RenderData->ProjectionMatrix, mesh, material, objID);
		s_RenderData->Stats.QuadCount++;
	}
	void Renderer::DrawLine(const glm::vec3 start, const glm::vec3 end, const glm::vec4 color, int objID)
	{
		EulerBatch::SubmitLine(s_RenderData->ViewMatrix, s_RenderData->ProjectionMatrix, start, end, color, objID);
		s_RenderData->Stats.LineCount++;
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
		s_RenderData->Stats.RectCount++;
	}
	void Renderer::DrawRect(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color, int objID)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		model *= glm::toMat4(glm::quat(rotation));
		model = glm::scale(model, scale);
		glm::vec3 LineVertices[QUAD_VERTEX_CNT];
		glm::vec4 QuadPositions[QUAD_VERTEX_CNT];
		for (unsigned int i = 0; i < QUAD_VERTEX_CNT; i++) {
			unsigned int head_index = QUAD_DATA_SIZE * i;
			glm::vec4 VerticePosition
				= glm::vec4(QuadVertices[head_index], QuadVertices[head_index + 1], QuadVertices[head_index + 2], 1.0f);
			QuadPositions[i] = VerticePosition;
		}

		for (unsigned int i = 0; i < QUAD_VERTEX_CNT; i++) {
			LineVertices[i] = model * QuadPositions[i];
		}
		DrawLine(LineVertices[0], LineVertices[1], color);
		DrawLine(LineVertices[1], LineVertices[2], color);
		DrawLine(LineVertices[2], LineVertices[3], color);
		DrawLine(LineVertices[3], LineVertices[0], color);

		s_RenderData->Stats.RectCount++;
	}
	void Renderer::DrawCircle(const glm::vec2 position, const float radius, const glm::vec4 color, int objID)
	{
		DrawCircle({ position.x, position.y, 0.0f }, radius, color, objID);
	}
	void Renderer::DrawCircle(const glm::vec3 position, const float radius, const glm::vec4 color, int objID)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		glm::vec3 LineVertices[CIRCLE_VERTEX_CNT];
		glm::vec4 CirclePositions[CIRCLE_VERTEX_CNT];
		for (unsigned int i = 0; i < CIRCLE_VERTEX_CNT; i++) {
			float angle = 2.0f * glm::pi<float>() * i / CIRCLE_VERTEX_CNT;
			CirclePositions[i] = glm::vec4(glm::cos(angle) * radius, glm::sin(angle) * radius, 0.0f, 1.0f);
			LineVertices[i] = model * CirclePositions[i];
		}

		for (unsigned int i = 0; i < CIRCLE_VERTEX_CNT - 1; i++) {
			DrawLine(LineVertices[i], LineVertices[i + 1], color, objID);
		}
		DrawLine(LineVertices[CIRCLE_VERTEX_CNT - 1], LineVertices[0], color, objID);

		s_RenderData->Stats.CircleCount++;
	}
	void Renderer::DrawCircle(const glm::vec2 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color, int objID)
	{
		DrawCircle({ position.x, position.y, 0.0f }, rotation, scale, color, objID);
	}
	void Renderer::DrawCircle(const glm::vec3 position, const glm::vec3 rotation, const glm::vec3 scale, const glm::vec4 color, int objID)
	{
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
		model *= glm::toMat4(glm::quat(rotation));
		model = glm::scale(model, scale);

		glm::vec4 CircleVertices[CIRCLE_VERTEX_CNT];
		for (unsigned int i = 0; i < CIRCLE_VERTEX_CNT; i++) {
			float angle = 2.0f * glm::pi<float>() * i / CIRCLE_VERTEX_CNT;
			CircleVertices[i] = glm::vec4(glm::cos(angle), glm::sin(angle), 0.0f, 1.0f);
		}

		glm::vec3 LineVertices[CIRCLE_VERTEX_CNT];
		glm::vec4 CirclePositions[CIRCLE_VERTEX_CNT];

		for (unsigned int i = 0; i < CIRCLE_VERTEX_CNT; i++) {
			CirclePositions[i] = model * CircleVertices[i];
		}

		for (unsigned int i = 0; i < CIRCLE_VERTEX_CNT - 1; i++) {
			DrawLine(LineVertices[i], LineVertices[i + 1], color, objID);
		}
		DrawLine(LineVertices[CIRCLE_VERTEX_CNT - 1], LineVertices[0], color, objID);

		s_RenderData->Stats.CircleCount++;
	}
	void Renderer::ResetStatistic()
	{
		memset(&s_RenderData->Stats, 0, sizeof(Statistics));
	}
	Renderer::Statistics Renderer::GetStats()
	{
		return s_RenderData->Stats;
	}
}