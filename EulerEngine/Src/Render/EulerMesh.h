#pragma once
#include"gkpch.h"
#include"Math/EulerMath.h"
#include"EulerShader.h"
#include"VertexArray.h"
#include"RenderCmd.h"
#include<glad/glad.h>
namespace EulerEngine {
	class Mesh {
	public:
		struct Vertex {
			glm::vec3 Position;
			glm::vec2 TexCoords;
			glm::vec3 Normal;
		};
		struct Triangle {
			Vertex vertexs[3];
		};
		float* vertices;
		std::vector<unsigned int> indices;
		Ref<VertexBuffer> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;
		Mesh(float* v, std::vector<unsigned int> i): vertices(v), indices(i) {
			Ref<VertexBuffer> vertexBuffer;
			vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float2, "a_TexCoord"},
			};
			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			unsigned int indices[3]{ 0, 1, 2 };
			Ref<IndexBuffer> indexBuffer;
			indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
			m_VertexArray->SetIndexBuffer(indexBuffer);
		}
		void Draw() {
			m_VertexArray->Bind();
			RenderCommand::DrawIndexed(m_VertexArray);
			m_VertexArray->Unbind();
		}
	private:
		Ref<VertexArray> m_VertexArray;
	};
}
