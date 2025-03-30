#pragma once
#include"Render/VertexArray.h"
#include"Render/EulerBuffer.h"
#include"Render/RawData/EulerMesh.h"
#include"Render/RawData/EulerMaterial.h"
#include"Render/EulerShader.h"
#define MAX_TEXTURE_SLOTS 32
#define LINE_WIDTH 1.0f
namespace EulerEngine {
	template<typename Vertex>
	class BatchData {
		unsigned int m_MaxCount = 0;
		unsigned int m_SingleVerticeCount = 0;
		unsigned int m_SingleIndiceCount = 0;
		Ref<VertexArray> m_VA;
		Ref<VertexBuffer> m_VB;
		Ref<IndexBuffer> m_IB;
		Vertex* m_VertexBase = nullptr;
		Ref<EulerShader> m_Shader;

		std::array<Ref<Texture2D>, MAX_TEXTURE_SLOTS> m_Texture2DSlots;
		unsigned int m_Texture2DSlotLoadedCount = 0;
		bool m_UseIndex = false;
	public:
		Vertex* m_VertexArrayPtr = nullptr;
		unsigned int m_VertexCount = 0;
		unsigned int m_IndexCount = 0;
	public:
		BatchData() = default;
		void BatchInit(unsigned int maxCount, unsigned int singleVerticeCount) {
			m_MaxCount = maxCount;
			m_SingleVerticeCount = singleVerticeCount;

			unsigned int maxTotalVerticeCount = m_MaxCount * m_SingleVerticeCount;

			m_VA = VertexArray::Create();
			m_VB = VertexBuffer::Create(maxTotalVerticeCount * sizeof(Vertex));
			m_VB->SetLayout(BufferLayout::GetLayoutFromVertexType<Vertex>());
			m_VA->AddVertexBuffer(m_VB);
			m_VertexBase = new Vertex[maxTotalVerticeCount];

			for (unsigned int i = 0; i < MAX_TEXTURE_SLOTS; i++) {
				m_Texture2DSlots[i] = 0;
			}
		}
		void BatchShutdown() {
			delete[] m_VertexBase;
		}
		void BatchClear() {
			m_VertexCount = 0;
			m_IndexCount = 0;
			m_VertexArrayPtr = m_VertexBase;
			m_Texture2DSlotLoadedCount = 0;
		}
		bool BatchFlush() {
			if (m_VertexArrayPtr != m_VertexBase) {
				unsigned int byte_offset = (unsigned int)((uint8_t*)m_VertexArrayPtr - (uint8_t*)m_VertexBase);
				m_VB->SetData(m_VertexBase, byte_offset);

				m_Shader->Bind();
				if constexpr (std::is_same<Vertex, LineVertex>::value) {
					RenderCommand::SetLineWidth(LINE_WIDTH);
					RenderCommand::DrawLines(m_VA, m_VertexCount);
					return true;
				}

				for (unsigned int i = 0; i < m_Texture2DSlotLoadedCount; i++) {
					m_Texture2DSlots[i]->Bind(i);
				}
				if (m_UseIndex) {
					RenderCommand::DrawIndexed(m_VA, m_IndexCount);
				}
				else {
					RenderCommand::Draw(m_VA, m_VertexCount);
				}
				return true;
			}
			return false;
		}
		void BatchApplyUniforms(const glm::mat4& view, const glm::mat4& projection, const Ref<EulerMaterial>& material) {

			auto texture = material->GetTexture();
			int textureIndex = -1;
			if (texture != nullptr) {
				for (unsigned int i = 0; i < m_Texture2DSlotLoadedCount; i++) {
					if (*m_Texture2DSlots[i] == *texture) {
						textureIndex = i;
						break;
					}
				}

				if (textureIndex == -1) {
					textureIndex = m_Texture2DSlotLoadedCount;
					m_Texture2DSlots[m_Texture2DSlotLoadedCount++] = texture;
				}
			}
			else {
				textureIndex = -1;
				KINK_CORE_WARN("No texture found for this object");
			}

			m_Shader->Bind();
			m_Shader->SetMat4("view", view);
			m_Shader->SetMat4("projection", projection);
			m_Shader->SetInt("texture_index", textureIndex);
		}
		void SetIndexBuffer(unsigned int* singleIndices, unsigned int singleIndiceCount) {
			m_SingleIndiceCount = singleIndiceCount;
			unsigned int maxTotalIndiceCount = m_MaxCount * m_SingleIndiceCount;
			unsigned int* Indices = new unsigned int[maxTotalIndiceCount];
			unsigned int offset = 0;
			for (unsigned int i = 0; i < maxTotalIndiceCount; i += m_SingleIndiceCount) {
				unsigned int j = 0;
				for (unsigned j = 0; j < m_SingleIndiceCount; j++) {
					Indices[i + j] = offset + singleIndices[j];
				}
				offset += m_SingleVerticeCount;
			}
			m_IB = IndexBuffer::Create(Indices, maxTotalIndiceCount);
			m_VA->SetIndexBuffer(m_IB);
			delete[] Indices;
			m_UseIndex = true;
		}
		void SetShader(const Ref<EulerShader>& shader) { 
			m_Shader = shader; 
		}
		Ref<EulerShader>& GetShader(){ 
			return m_Shader; 
		}
	};
}