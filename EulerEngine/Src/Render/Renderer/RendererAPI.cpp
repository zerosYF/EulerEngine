#include"gkpch.h"
#include"RendererAPI.h"
#include"Platform/OpenGL/GLRendererAPI.h"

namespace EulerEngine {
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;
	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API) {
			case RendererAPI::API::None:    return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<GLRendererAPI>();
		}
		return nullptr;
	}
}