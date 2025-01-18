#include"gkpch.h"
#include"EulerTexture.h"
#include"Render/Renderer.h"
#include"Platform/OpenGL/GLTexture2D.h"
namespace EulerEngine {
	Texture2D* Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLTexture2D(path);
		}
		return nullptr;
	}
}