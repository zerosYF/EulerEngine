#include"gkpch.h"
#include"VertexArray.h"
#include"Renderer.h"
#include"Platform/OpenGL/GLVertexArray.h"
namespace EulerEngine {
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLVertexArray>();
		}
		return nullptr;
	}
}

