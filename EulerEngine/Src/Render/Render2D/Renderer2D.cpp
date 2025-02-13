#include"gkpch.h"
#include"Renderer2D.h"
#include"Render/VertexArray.h"
#include"Render/EulerShader.h"
#include"Render/Vertices/EulerVertices.h"
#include"Render/Renderer.h"
#include"Platform/OpenGL/GLShader.h"
#include<memory>
namespace EulerEngine {
	struct Renderer2DStorage {
		Ref<VertexArray> va;
		EulerEngine::ResourceLibrary s_ResourceLib;
		glm::mat4 view_matrix = glm::mat4(1.0f);
		glm::mat4 projection_matrix = glm::mat4(1.0f);
	};
	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->va = EulerEngine::VertexArray::Create();
		EulerEngine::Ref<EulerEngine::VertexBuffer> vertexBuffer
			= EulerEngine::VertexBuffer::Create(EulerEngine::SquareVerticesWithoutTexture, sizeof(EulerEngine::SquareVerticesWithoutTexture));
		vertexBuffer->SetLayout({
			{ EulerEngine::ShaderDataType::Float3, "aPosition" },
		});
		s_Data->va->AddVertexBuffer(vertexBuffer);

		unsigned int SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		EulerEngine::Ref<EulerEngine::IndexBuffer> indexBuffer
			= EulerEngine::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices)/sizeof(unsigned int));
		s_Data->va->SetIndexBuffer(indexBuffer);

		s_Data->s_ResourceLib.LoadShader("2d_quad", "Shaders/Camera/2d.glsl");
	}
	void Renderer2D::ShutDown()
	{
		delete s_Data;
	}
	void Renderer2D::BeginScene(const OrthoCamera& camera)
	{
		s_Data->view_matrix = camera.GetViewMatrix();
		s_Data->projection_matrix = camera.GetProjectionMatrix();
	}
	void Renderer2D::EndScene()
	{
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		auto shader = s_Data->s_ResourceLib.GetShader("2d_quad");
		
		shader->Bind();
		shader->SetMat4("view", s_Data->view_matrix);
		shader->SetMat4("projection", s_Data->projection_matrix);
		shader->SetVec4("color", color);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), {size.x, size.y, 1.0f});
		shader->SetMat4("model", model);
		s_Data->va->Bind();
		RenderCommand::Draw(s_Data->va);
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		auto shader = s_Data->s_ResourceLib.GetShader("2d_quad");
		shader->Bind();
		shader->SetMat4("view", s_Data->view_matrix);
		shader->SetMat4("projection", s_Data->projection_matrix);
		texture->Bind(0);
		shader->SetInt("texture", 0);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		shader->SetMat4("model", model);
		s_Data->va->Bind();
		RenderCommand::Draw(s_Data->va);
	}
}