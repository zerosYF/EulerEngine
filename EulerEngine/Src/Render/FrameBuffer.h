#pragma once
#include"GutKink/Core.h"
namespace EulerEngine {
	struct FrameBufferSpecifications
	{
		unsigned int Width;
		unsigned int Height;
		unsigned int Samples = 1;
		bool SwapChainTarget = false;
	};
	class FrameBuffer {
	public:
		virtual const FrameBufferSpecifications& GetSpecifications() const = 0;
		static Ref<FrameBuffer> Create(const FrameBufferSpecifications& specs);
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Resize(unsigned int width, unsigned int height) = 0;
		virtual unsigned int GetColorAttachmentRendererID() const = 0;
	};
}