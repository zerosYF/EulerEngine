#pragma once
#include "Render/FrameBuffer.h"
namespace EulerEngine {
	class GLFrameBuffer :public FrameBuffer {
	public:
		GLFrameBuffer(const FrameBufferSpecification& specifications);
		virtual ~GLFrameBuffer();
		void Invalidate();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Resize(unsigned int width, unsigned int height) override;
		virtual const FrameBufferSpecification& GetSpecifications() const override { return m_Specification; }
		virtual unsigned int GetColorAttachmentRendererID(unsigned int idx) const override { 
			KINK_CORE_ASSERT(idx < m_ColorAttachments.size(), "Index out of range");
			return m_ColorAttachments[idx]; 
		}
		
	private:
		unsigned int m_RendererID = 0;
		FrameBufferSpecification m_Specification;
		std::vector<FrameBufferTextureSpecification> m_ColorAttachmentSpecs;
		FrameBufferTextureSpecification m_DepthAttachmentSpec;
		std::vector<unsigned int> m_ColorAttachments;
		unsigned int m_DepthAttachment = 0;
	};
}