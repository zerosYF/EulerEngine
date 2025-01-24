#pragma once
#include<GLFW/glfw3.h>
#include"Platform/OpenGL/GLShader.h"
#include"Platform/OpenGL/GLTexture2D.h"
#include "stb_image/stb_image.h"
namespace EulerEngine {
	class ResourceLibrary {
	private:
		std::map<std::string, Ref<EulerShader>> m_Shaders;
		std::map<std::string, Ref<Texture2D>> m_Texture2Ds;
	public:
		void AddShader(const Ref<EulerShader>& shader);
		void AddShader(const std::string& name, const Ref<EulerShader>& shader);
		Ref<EulerShader> LoadShader(const std::string& path); 
		Ref<EulerShader> GetShader(const std::string& name);
		bool IsShaderExists(const std::string& name);
	private:
		
	};
}