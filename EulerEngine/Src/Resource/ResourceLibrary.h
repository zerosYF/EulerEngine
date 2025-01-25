#pragma once
#include<GLFW/glfw3.h>
#include"Render/EulerShader.h"
#include"Render/EulerTexture.h"
#include"Render/EulerMaterial.h"
#include "stb_image/stb_image.h"
namespace EulerEngine {
	class ResourceLibrary {
	private:
		std::unordered_map<std::string, Ref<EulerShader>> m_Shaders;
		std::unordered_map<std::string, Ref<Texture2D>> m_Texture2Ds;
		std::unordered_map<std::string, Ref<Material>> m_Materials;
	public:
		void AddShader(const std::string& name, const Ref<EulerShader>& shader);
		Ref<EulerShader> LoadShader(const std::string& name, const std::string& path);
		Ref<EulerShader> GetShader(const std::string& name);
		bool IsShaderExists(const std::string& name);

		void AddTexture2D(const std::string& name, const Ref<Texture2D>& texture);
		Ref<Texture2D> LoadTexture2D(const std::string& name, const std::string& path);
		Ref<Texture2D> GetTexture2D(const std::string& name);
		bool IsTexture2DExists(const std::string& name);

		void AddMaterial(const std::string& name, const Ref<Material>& material);
		Ref<Material> LoadMaterial(const std::string& name);
		Ref<Material> GetMaterial(const std::string& name);
		bool IsMaterialExists(const std::string& name);

	};
}