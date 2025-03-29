#include"gkpch.h"
#include"ResourceLibrary.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	std::unordered_map<Ref<EulerShader>,std::string> ResourceLibrary::s_ShaderMap;
	std::unordered_map<Ref<Texture2D>, std::string> ResourceLibrary::s_Texture2DMap;
	Ref<EulerShader> ResourceLibrary::LoadShader(const std::string & relative_path)
	{
		std::filesystem::path shader_path = Project::GetPath(std::string(relative_path));
		auto shader = EulerShader::Create(shader_path.string());
		KINK_CORE_INFO("Create shader success...");
		s_ShaderMap[shader] = relative_path;
		return shader;
	}
	Ref<Texture2D> ResourceLibrary::LoadTexture2D(const std::string & relative_path)
	{
		std::filesystem::path texture_path = Project::GetPath(std::string(relative_path));
		auto texture = Texture2D::Create(texture_path.string());
		s_Texture2DMap[texture] = relative_path;
		KINK_CORE_INFO("Create texture success...");
		return texture;
	}

	Ref<Texture2D> ResourceLibrary::LoadTexture2DInner(const std::string& path)
	{
		auto texture = Texture2D::Create("Assets/Editor/" +path);
		return texture;
	}

	Ref<EulerShader> ResourceLibrary::LoadShaderInner(const std::string& path)
	{
		auto shader = EulerShader::Create("Assets/Shaders/" + path);
		return shader;
	}


	const std::string ResourceLibrary::GetShaderInnerPath(Ref<EulerShader> shader)
	{
		return s_ShaderMap[shader];
	}

	const std::string ResourceLibrary::GetTexture2DResourcePath(Ref<Texture2D> texture)
	{
		return s_Texture2DMap[texture];
	}

}