#pragma once
#include"gkpch.h"
#include"Math/EulerMath.h"
#include"EulerShader.h"
#include"VertexArray.h"
#include"EulerMaterial.h"
#include"Renderer/RenderCmd.h"
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
		Mesh(float* vertices, std::vector<unsigned int> indices) {
			Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

			BufferLayout layout = {
				{ShaderDataType::Float3, "aPosition"},
				{ShaderDataType::Float2, "aTexCoord"},
				{ShaderDataType::Float3, "aNormal"},
			};
			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), sizeof(indices) / sizeof(unsigned int));
			m_VertexArray->SetIndexBuffer(indexBuffer);
		}
		void Draw() {
			m_VertexArray->Bind();
			RenderCommand::Draw(m_VertexArray);
			m_VertexArray->Unbind();
		}
	private:
		Ref<VertexArray> m_VertexArray;
	};
}
