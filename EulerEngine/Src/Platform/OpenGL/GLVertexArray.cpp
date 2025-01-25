#include"gkpch.h"
#include"GLVertexArray.h"
namespace EulerEngine {
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexbuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexbuffer->Bind();
		const auto& layout = vertexbuffer->GetLayout();
		unsigned int index = 0;
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexbuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer>& indexbuffer)
	{
		glBindVertexArray(m_RendererID);
		indexbuffer->Bind();
		m_IndexBuffer = indexbuffer;
	}
}