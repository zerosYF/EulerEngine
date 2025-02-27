#include"gkpch.h"
#include"FrameBuffer.h"
#include"Platform/OpenGL/GLFrameBuffer.h"
#include"Renderer/Renderer.h"
namespace EulerEngine {
	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& specs)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<GLFrameBuffer>(specs);
		}
		return nullptr;
	}
}