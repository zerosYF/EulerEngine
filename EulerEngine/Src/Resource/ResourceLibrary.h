#pragma once
#include<GLFW/glfw3.h>
#include"Render/EulerShader.h"
#include"Render/Texture/EulerTexture.h"
#include"Render/EulerMaterial.h"
#include"stb_image/stb_image.h"
#include"Project/EulerProject.h"
#include<filesystem>
namespace EulerEngine {
	class ResourceLibrary {
	public:
		static Ref<EulerShader> LoadShaderInner(const std::string& path);
		static Ref<Texture2D> LoadTexture2D(const std::string& path);
	};
}