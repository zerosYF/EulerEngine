#pragma once
#include"GutKink/Core.h"
namespace EulerEngine {
	enum class FrameBufferTextureFormat {
		None = 0,
		RGBA8,
		DEPTH24STENCIL8,
		Depth = DEPTH24STENCIL8
	};
	struct FrameBufferTextureSpecification {
		FrameBufferTextureSpecification() = default;
		FrameBufferTextureSpecification(FrameBufferTextureFormat format) : Format(format) {}
		FrameBufferTextureFormat Format = FrameBufferTextureFormat::None;
	};
	struct FrameBufferAttachmentSpecification {
		FrameBufferAttachmentSpecification() = default;
		FrameBufferAttachmentSpecification(const std::initializer_list<FrameBufferTextureSpecification> texturespecs): TextureSpecs(texturespecs) {}
		std::vector<FrameBufferTextureSpecification> TextureSpecs;
	};

	struct FrameBufferSpecification
	{
		unsigned int Width;
		unsigned int Height;
		FrameBufferAttachmentSpecification Attachments;
		unsigned int Samples = 1;
		bool SwapChainTarget = false;
	};
	class FrameBuffer {
	public:
		virtual const FrameBufferSpecification& GetSpecifications() const = 0;
		static Ref<FrameBuffer> Create(const FrameBufferSpecification& specs);
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;
		virtual unsigned int GetColorAttachmentRendererID(unsigned int idx) const = 0;
	};
}