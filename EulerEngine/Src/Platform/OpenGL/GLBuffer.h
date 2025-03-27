#pragma once
#include "Render/EulerBuffer.h"
namespace EulerEngine {
	class OpenGLVertexBuffer :public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		OpenGLVertexBuffer(unsigned int size);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout;  }
		virtual void SetData(const void* data, unsigned int size) override;
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
	private:
		unsigned int m_RendererID;
		BufferLayout m_Layout;
	};
	class OpenGLIndexBuffer :public IndexBuffer {
	public:
		OpenGLIndexBuffer(unsigned int* indices, unsigned int count);
		OpenGLIndexBuffer(unsigned int count);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetData(const void* data, unsigned int count) override;
		virtual unsigned int GetCount() const override { return m_Count; }
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;
	};
}