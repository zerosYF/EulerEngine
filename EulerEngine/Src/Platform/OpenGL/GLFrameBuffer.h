#pragma once
#include "Render/FrameBuffer.h"
namespace EulerEngine {
	class GLFrameBuffer :public FrameBuffer {
	public:
		GLFrameBuffer(const FrameBufferSpecifications& specifications);
		virtual ~GLFrameBuffer();
		void Invalidate();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual const FrameBufferSpecifications& GetSpecifications() const override { return m_Specifications; }
		virtual unsigned int GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		
	private:
		unsigned int m_RendererID;
		unsigned int m_ColorAttachment;
		unsigned int m_DepthAttachment;
		FrameBufferSpecifications m_Specifications;
	};
}