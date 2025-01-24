#include"gkpch.h"
#include"ResourceLibrary.h"
namespace EulerEngine {
	void ResourceLibrary::AddShader(const std::string & name, const Ref<EulerShader>& shader)
	{
		m_Shaders[name] = shader;
	}
	Ref<EulerShader> ResourceLibrary::LoadShader(const std::string& name, const std::string & path)
	{
		auto shader = EulerShader::Create(path);
		this->AddShader(name, shader);
		return shader;
	}
	Ref<EulerShader> ResourceLibrary::GetShader(const std::string & name)
	{
		return m_Shaders[name];
	}
	bool ResourceLibrary::IsShaderExists(const std::string & name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}




	void ResourceLibrary::AddTexture2D(const std::string & name, const Ref<Texture2D> texture)
	{
		m_Texture2Ds[name] = texture;
	}
	Ref<Texture2D> ResourceLibrary::LoadTexture2D(const std::string& name, const std::string & path, TextureType type)
	{
		auto texture = Texture2D::Create(path, type);
		this->AddTexture2D(name, texture);
		return texture;
	}
	Ref<Texture2D> ResourceLibrary::GetTexture2D(const std::string & name)
	{
		return m_Texture2Ds[name];
	}
	bool ResourceLibrary::IsTexture2DExists(const std::string & name)
	{
		return m_Texture2Ds.find(name) != m_Texture2Ds.end();
	}





	void ResourceLibrary::AddMaterial(const std::string name, Ref<Material>& material)
	{
		m_Materials[name] = material;
	}
	Ref<Material> ResourceLibrary::GetMaterial(const std::string & name)
	{
		auto iter = m_Materials.find(name);
		return iter != m_Materials.end() ? iter->second : nullptr;
	}
	bool ResourceLibrary::IsMaterialExists(const std::string & name)
	{
		return m_Materials.find(name) != m_Materials.end();
	}
}