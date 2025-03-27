#include"gkpch.h"
#include"EulerMaterial.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	EulerMaterial::EulerMaterial(): m_Albedo(glm::vec3(1.0f)), m_Roughness(0.5f)
	{
	}
	void EulerMaterial::SetShader(Ref<EulerShader> shader)
	{
	}
	void EulerMaterial::SetTexture(Ref<Texture2D> texture)
	{
	}
	void EulerMaterial::SetAlbedo(glm::vec3 albedo)
	{
	}
	void EulerMaterial::SetRoughness(float roughness)
	{
	}
	void EulerMaterial::AddFloatParam(std::string& name, float param)
	{
	}
	Ref<EulerShader>& EulerMaterial::GetShader()
	{
		// TODO: 在此处插入 return 语句
		return m_Shader;
	}
	Ref<Texture2D>& EulerMaterial::GetTexture()
	{
		// TODO: 在此处插入 return 语句
		return m_Texture;
	}
	glm::vec3& EulerMaterial::GetAlbedo()
	{
		// TODO: 在此处插入 return 语句
		return m_Albedo;
	}
	float& EulerMaterial::GetRoughness()
	{
		// TODO: 在此处插入 return 语句
		return m_Roughness;
	}
	float EulerMaterial::GetFloatParam(const std::string& name) const
	{
		return 0.0f;
	}
	void EulerMaterial::Apply(int texture_slot) const
	{
	}
	Ref<EulerMaterial> EulerMaterial::Create()
	{
		return CreateRef<EulerMaterial>();
	}
}