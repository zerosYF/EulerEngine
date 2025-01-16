#include"gkpch.h"
#include"VertexArray.h"
#include"Renderer.h"
#include"Platform/OpenGL/GLVertexArray.h"
namespace EulerEngine {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
		return nullptr;
	}
}

