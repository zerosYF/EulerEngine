#include"gkpch.h"
#include"EulerMaterial.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	EulerMaterial3D::EulerMaterial3D(): m_Albedo(glm::vec3(1.0f)), m_Roughness(0.5f)
	{
	}
	void EulerMaterial3D::SetShader(Ref<EulerShader> shader)
	{
		m_Shader = shader;
	}
	void EulerMaterial3D::SetTexture(Ref<Texture2D> texture)
	{
		m_Texture = texture;
	}
	void EulerMaterial3D::SetAlbedo(glm::vec3 albedo)
	{
		m_Albedo = albedo;
	}
	void EulerMaterial3D::SetRoughness(float roughness)
	{
		m_Roughness = roughness;
	}
	void EulerMaterial3D::AddFloatParam(std::string& name, float param)
	{
		m_Paramters[name] = param;
	}
	Ref<EulerShader>& EulerMaterial3D::GetShader()
	{
		return m_Shader;
	}
	Ref<Texture2D>& EulerMaterial3D::GetTexture()
	{
		return m_Texture;
	}
	glm::vec3& EulerMaterial3D::GetAlbedo()
	{
		return m_Albedo;
	}
	float& EulerMaterial3D::GetRoughness()
	{
		return m_Roughness;
	}
	float EulerMaterial3D::GetFloatParam(const std::string& name) const
	{
		return 0.0f;
	}
	void EulerMaterial3D::Apply(int texture_slot) const
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