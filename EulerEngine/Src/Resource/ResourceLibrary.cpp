#include"gkpch.h"
#include"ResourceLibrary.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	Ref<EulerShader> ResourceLibrary::LoadShaderInner(const std::string & path)
	{
		auto shader = EulerShader::Create("Assets/Shaders/" + path);
		KINK_CORE_INFO("Create shader success...");
		return shader;
	}
	Ref<Texture2D> ResourceLibrary::LoadTexture2D(const std::string & path)
	{
		std::string path_ = "Resource/" + path;
		std::filesystem::path texture_path = Project::GetAssetFileSystemPath(path_);
		auto texture = Texture2D::Create(texture_path.string());
		KINK_CORE_INFO("Create texture success...");
		return texture;
	}
}