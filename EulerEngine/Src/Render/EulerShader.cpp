#include"gkpch.h"
#include"EulerShader.h"
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include"Render/Renderer.h"
#include"Platform/OpenGL/GLShader.h"
namespace EulerEngine {
	EulerShader* EulerShader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		return nullptr;
	}
}