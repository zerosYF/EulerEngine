#include"gkpch.h"
#include"GLFrameBuffer.h"
#include"Core/Logs/EulerLog.h"
#include"glad/glad.h"
namespace EulerEngine {
	static const unsigned int s_MaxFramebufferSize = 8192;
	static GLenum TextureTarget(bool multisampled) {
		return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
	}
	static bool IsDepthFormat(FrameBufferTextureFormat format) {
		switch (format) {
		case FrameBufferTextureFormat::DEPTH24STENCIL8:
			return true;
		}
		return false;
	}
	static GLenum KinkFrameBufferTextureFormatToOpenGL(FrameBufferTextureFormat format) {
		switch (format) {
		case FrameBufferTextureFormat::RGBA8:
			return GL_RGBA8;
		case FrameBufferTextureFormat::RED_INTEGER:
			return GL_RED_INTEGER;
		}
		KINK_CORE_ASSERT(false, "Unknown texture format!");
		return 0;
	}
	static GLenum GLDataTypeFromFrameBufferTextureFormat(FrameBufferTextureFormat format) {
		switch (format) {
		case FrameBufferTextureFormat::RGBA8:
			return GL_UNSIGNED_BYTE;
		case FrameBufferTextureFormat::RED_INTEGER:
			return GL_INT;
		}
		KINK_CORE_ASSERT(false, "Unknown texture format!");
		return 0;
	}

	static void CreateTextures(unsigned int* outTextures, unsigned int count) {
		glGenTextures(count, outTextures);
	}
	static void BindTexture(bool multisampled, unsigned int texture_id) {
		glBindTexture(TextureTarget(multisampled), texture_id);
	}
	static void AttachColorTexture(unsigned int textureAttachmentID, unsigned int samples, GLenum internal_format, GLenum format, int width, int height, unsigned int idx) {
		bool multisampled = samples > 1;
		if (multisampled) {
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + idx, TextureTarget(multisampled), textureAttachmentID, 0);
	}
	static void AttachDepthTexture(unsigned int depthAttachmentID, unsigned int samples, GLenum format, GLenum attachmentType, int width, int height) {
		bool multiplesampled = samples > 1;
		if (multiplesampled) {
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multiplesampled), depthAttachmentID, 0);
	}
	GLFrameBuffer::GLFrameBuffer(const FrameBufferSpecification& specification):m_Specification(specification)
	{
		for (auto spec: m_Specification.Attachments.TextureSpecs) {
			if (IsDepthFormat(spec.Format)) {
				m_DepthAttachmentSpec = spec;
			}
			else {
				m_ColorAttachmentSpecs.emplace_back(spec);
			}
		}
		Invalidate();
	}
	GLFrameBuffer::~GLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);
	}
	void GLFrameBuffer::Invalidate()
	{
		if (m_RendererID) {
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);

			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}
		glGenFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		bool multisampled = m_Specification.Samples > 1;
		if (m_ColorAttachmentSpecs.size()) {
			m_ColorAttachments.resize(m_ColorAttachmentSpecs.size());
			CreateTextures(m_ColorAttachments.data(), m_ColorAttachments.size());

			for (unsigned int i = 0; i < m_ColorAttachments.size(); i++) {
				BindTexture(multisampled, m_ColorAttachments[i]);
				switch (m_ColorAttachmentSpecs[i].Format) {
				case FrameBufferTextureFormat::RGBA8:
					AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_RGBA8, GL_RGBA, m_Specification.Width, m_Specification.Height, i);
					break;
				case FrameBufferTextureFormat::RED_INTEGER:
					AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_R32I, GL_RED_INTEGER, m_Specification.Width, m_Specification.Height, i);
					break;
				}
			}
		}

		if (m_DepthAttachmentSpec.Format != FrameBufferTextureFormat::None) {
			KINK_INFO("Depth attachment is supported yet!");
			CreateTextures(&m_DepthAttachment, 1);
			BindTexture(multisampled, m_DepthAttachment);
			switch (m_DepthAttachmentSpec.Format) {
			case FrameBufferTextureFormat::DEPTH24STENCIL8:
				KINK_INFO("Depth attachment ID:{0}", m_DepthAttachment);
				AttachDepthTexture(m_DepthAttachment, m_Specification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.Width, m_Specification.Height);
				break;
			}
		}

		if (m_ColorAttachments.size() > 1) {
			KINK_CORE_ASSERT(m_ColorAttachments.size() <= 4, "Framebuffer can have at most 4 color attachments!");
			GLenum buffers[4] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
			glDrawBuffers(m_ColorAttachments.size(), buffers);
		}
		else if (m_ColorAttachments.empty()) {
			glDrawBuffer(GL_NONE);
		}

		KINK_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void GLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}
	void GLFrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void GLFrameBuffer::Resize(unsigned int width, unsigned int height)
	{
		m_Specification.Width = width;
		m_Specification.Height = height;
		KINK_CORE_ASSERT(width > 0 && height > 0, "Framebuffer size cannot be zero!");
		Invalidate();
	}
	int GLFrameBuffer::ReadPixel(unsigned int attachmentIndex, int x, int y)
	{
		KINK_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size(), "Invalid attachment index!");
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixel;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixel);
		return pixel;
	}
	void GLFrameBuffer::ClearAttachment(unsigned int attachmentIndex, int value)
	{
		KINK_CORE_ASSERT(attachmentIndex < m_ColorAttachments.size(), "Invalid attachment index!");
		auto& spec = m_ColorAttachmentSpecs[attachmentIndex];
		glClearTexImage(m_ColorAttachments[attachmentIndex], 0,
			KinkFrameBufferTextureFormatToOpenGL(spec.Format), GL_INT, &value);
	}
}

