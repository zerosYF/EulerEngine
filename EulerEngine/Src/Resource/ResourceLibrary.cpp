#include"gkpch.h"
#include"ResourceLibrary.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	ResourceLibrary* ResourceLibrary::s_Instance = nullptr;
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
		auto iter = m_Shaders.find(name);
		return iter != m_Shaders.end() ? iter->second : nullptr;
	}
	bool ResourceLibrary::IsShaderExists(const std::string & name)
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}




	void ResourceLibrary::AddTexture2D(const std::string & name, const Ref<Texture2D>& texture)
	{
		m_Texture2Ds[name] = texture;
	}
	Ref<Texture2D> ResourceLibrary::LoadTexture2D(const std::string& name, const std::string & path)
	{
		auto texture = Texture2D::Create(path);
		KINK_CORE_INFO("Create texture success...");
		this->AddTexture2D(name, texture);
		KINK_CORE_INFO("Add texture success...");
		return texture;
	}
	Ref<Texture2D> ResourceLibrary::GetTexture2D(const std::string & name)
	{
		auto iter = m_Texture2Ds.find(name);
		return iter != m_Texture2Ds.end() ? iter->second : nullptr;
	}
	bool ResourceLibrary::IsTexture2DExists(const std::string & name)
	{
		return m_Texture2Ds.find(name) != m_Texture2Ds.end();
	}





	void ResourceLibrary::AddMaterial(const std::string& name, const Ref<Material>& material)
	{
		m_Materials[name] = material;
	}
	Ref<Material> ResourceLibrary::LoadMaterial(const std::string & name)
	{
		auto material = Material::Create();
		this->AddMaterial(name, material);
		return material;
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
	ResourceLibrary* ResourceLibrary::GetResourceLibrary()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new ResourceLibrary();
		}
		return s_Instance;
	}
}