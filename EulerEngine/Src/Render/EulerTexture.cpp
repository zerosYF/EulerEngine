#include"gkpch.h"
#include"EulerTexture.h"
#include"Render/Renderer.h"
#include"Platform/OpenGL/GLTexture2D.h"
namespace EulerEngine {
	Ref<Texture2D> Texture2D::Create(const std::string& path, TextureType type) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path, type);
		}
		return nullptr;
	}
}