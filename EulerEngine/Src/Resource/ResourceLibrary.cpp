#include"gkpch.h"
#include"ResourceLibrary.h"
namespace EulerEngine {
	void ResourceLibrary::AddShader(const Ref<EulerShader>& shader)
	{
		auto& name = shader->GetName();
		m_Shaders[name] = shader;
	}
	void ResourceLibrary::AddShader(const std::string & name, const Ref<EulerShader>& shader)
	{
		m_Shaders[name] = shader;
	}
	Ref<EulerShader> ResourceLibrary::LoadShader(const std::string & path)
	{
		auto shader = EulerShader::Create(path);
		this->AddShader(shader);
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
}