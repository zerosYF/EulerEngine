#include"gkpch.h"
#include"FrameBuffer.h"
#include"Platform/OpenGL/GLFrameBuffer.h"
#include"Renderer.h"
namespace EulerEngine {
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecifications& specs)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<GLFrameBuffer>(specs);
		}
		return nullptr;
	}
}