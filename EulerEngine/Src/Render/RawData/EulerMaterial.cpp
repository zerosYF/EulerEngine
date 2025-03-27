#include"gkpch.h"
#include"EulerMaterial.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	EulerMaterial::EulerMaterial(): m_Albedo(glm::vec3(1.0f)), m_Roughness(0.5f)
	{
	}
	void EulerMaterial::SetShader(Ref<EulerShader> shader)
	{
		m_Shader = shader;
	}
	void EulerMaterial::SetTexture(Ref<Texture2D> texture)
	{
		m_Texture = texture;
	}
	void EulerMaterial::SetAlbedo(glm::vec3 albedo)
	{
		m_Albedo = albedo;
	}
	void EulerMaterial::SetRoughness(float roughness)
	{
		m_Roughness = roughness;
	}
	void EulerMaterial::AddFloatParam(std::string& name, float param)
	{
		m_Paramters[name] = param;
	}
	Ref<EulerShader>& EulerMaterial::GetShader()
	{
		return m_Shader;
	}
	Ref<Texture2D>& EulerMaterial::GetTexture()
	{
		return m_Texture;
	}
	glm::vec3& EulerMaterial::GetAlbedo()
	{
		return m_Albedo;
	}
	float& EulerMaterial::GetRoughness()
	{
		return m_Roughness;
	}
	float EulerMaterial::GetFloatParam(const std::string& name) const
	{
		return 0.0f;
	}
	void EulerMaterial::Apply(int texture_slot) const
	{
		m_Shader->Bind();
		m_Shader->SetVec3("u_Material.albedo", m_Albedo);
		m_Shader->SetFloat("u_Material.roughness", m_Roughness);
		if (m_Texture)
		{
			m_Texture->Bind(texture_slot);
			m_Shader->SetInt("texture_index", texture_slot);
		}
		else
		{
			m_Shader->SetInt("texture_index", -1);
		}
		for (auto& param : m_Paramters)
		{
			m_Shader->SetFloat(param.first.c_str(), param.second);
		}
	}
}