#include"gkpch.h"
#include"EulerShader.h"
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include"Renderer/Renderer.h"
#include"Platform/OpenGL/GLShader.h"
namespace EulerEngine {
	Ref<EulerShader> EulerShader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(vertexSrc, fragmentSrc);
		}
		return nullptr;
	}
	Ref<EulerShader> EulerShader::Create(const std::string & path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(path);
		}
		return nullptr;
	}
}