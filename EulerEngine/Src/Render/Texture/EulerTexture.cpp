#include"gkpch.h"
#include"EulerTexture.h"
#include"Render/Renderer/Renderer.h"
#include"Platform/OpenGL/GLTexture2D.h"
namespace EulerEngine {
	Ref<Texture2D> Texture2D::Create(const std::string& path) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(path);
		}
		return nullptr;
	}
	Ref<Texture2D> Texture2D::Create(unsigned int width, unsigned int height) {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLTexture2D>(width, height);
		}
		return nullptr;
	}
}