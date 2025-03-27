#pragma once
#include<GLFW/glfw3.h>
#include"Render/EulerShader.h"
#include"Render/RawData/EulerTexture.h"
#include"Render/RawData/EulerMaterial.h"
#include"Render/RawData/EulerMaterial2D.h"
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