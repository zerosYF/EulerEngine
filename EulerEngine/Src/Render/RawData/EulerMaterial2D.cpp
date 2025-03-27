#include"gkpch.h"
#include"EulerMaterial2D.h"
namespace EulerEngine {
	Ref<EulerMaterial2D> EulerMaterial2D::Create()
	{
		return CreateRef<EulerMaterial2D>();
	}

	EulerMaterial2D::EulerMaterial2D() {
		m_Color = glm::vec4(1.0f);
	}
	void EulerMaterial2D::SetShader(Ref<EulerShader> shader)
	{
		m_Shader = shader;
	}
	void EulerMaterial2D::SetTexture(Ref<Texture2D> texture) {
		m_Texture = texture;
	}

	void EulerMaterial2D::SetColor(glm::vec4 color)
	{
		m_Color = color;
	}

	void EulerMaterial2D::AddFloatParam(std::string& name, float param)
	{
		m_Paramters[name] = param;
	}

	Ref<EulerShader>& EulerMaterial2D::GetShader()
	{
		return m_Shader;
	}

	glm::vec4& EulerMaterial2D::GetColor()
	{
		return m_Color;
	}

	Ref<Texture2D>& EulerMaterial2D::GetTexture()
	{
		return m_Texture;
	}

	float EulerMaterial2D::GetFloatParam(const std::string& name) const
	{
		auto it = m_Paramters.find(name);
		return it != m_Paramters.end() ? it->second : 0;
	}

	void EulerMaterial2D::Apply(int texture_slot) const
	{
		m_Shader->Bind();
		m_Texture->Bind(texture_slot);
		for (const auto& [name, param] : m_Paramters) {
			m_Shader->SetFloat(name, param);
		}
		m_Shader->SetVec4("color", m_Color);
	}
}