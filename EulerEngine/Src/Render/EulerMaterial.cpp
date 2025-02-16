#include"gkpch.h"
#include"EulerMaterial.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	Ref<Material> Material::Create()
	{
		return CreateRef<Material>();
	}

	Material::Material() {
		m_Color = glm::vec4(1.0f);

		KINK_CORE_INFO("Material init...");
	}
	void Material::SetTexture(Ref<Texture2D> texture) {
		m_Texture = texture;
		KINK_CORE_INFO("Material add Texture success...");
	}

	void Material::SetColor(glm::vec4 color)
	{
		m_Color = color;
	}

	void Material::AddFloatParam(std::string& name, float param)
	{
		m_Paramters[name] = param;
	}

	glm::vec4 Material::GetColor() const
	{
		return m_Color;
	}

	Ref<Texture2D> Material::GetTexture() const
	{
		return m_Texture;
	}

	float Material::GetFloatParam(const std::string & name) const
	{
		auto it = m_Paramters.find(name);
		return it != m_Paramters.end() ? it->second : 0;
	}

	void Material::Apply(Ref<EulerShader>& shader, int texture_slot) const
	{
		shader->Bind();
		m_Texture->Bind(texture_slot);
		for (const auto& [name, param]:m_Paramters) {
			shader->SetFloat(name, param);
		}
		shader->SetVec4("color", m_Color);
	}

	/*void Material::setSpotLightRender(EulerSpotLight* light) {
		m_Shader->SetVec3("spotLight.ambient", light_material.ambient*light->color);
		m_Shader->SetVec3("spotLight.diffuse", light_material.diffuse*light->color);
		m_Shader->SetVec3("spotLight.specular", light_material.specular*light->color);
		m_Shader->SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(light->outerCutOff)));
		m_Shader->SetFloat("spotLight.cutOff", glm::cos(glm::radians(light->cutOff)));
		m_Shader->SetVec3("spotLight.direction", light->direction);
		m_Shader->SetVec3("spotLight.position", light->transform.position);
		m_Shader->SetFloat("spotLight.constant", light->constant);
		m_Shader->SetFloat("spotLight.linear", light->linear);
		m_Shader->SetFloat("spotLight.quatratic", light->quatratic);
	}
	void Material::setPointLightRender(EulerPointLight* light) {
		m_Shader->SetVec3("pointLight.position", light->transform.position);
		m_Shader->SetVec3("pointLight.ambient", light_material.ambient*light->color);
		m_Shader->SetVec3("pointLight.diffuse", light_material.diffuse*light->color);
		m_Shader->SetVec3("pointLight.specular", light_material.specular*light->color);
		m_Shader->SetFloat("pointLight.constant", light->constant);
		m_Shader->SetFloat("pointLight.linear", light->linear);
		m_Shader->SetFloat("pointLight.quatratic", light->quatratic);
	}
	void Material::setDirLightRender(EulerDirLight* light) {
		m_Shader->SetVec3("dirLight.ambient", light_material.ambient*light->color);
		m_Shader->SetVec3("dirLight.diffuse", light_material.diffuse*light->color);
		m_Shader->SetVec3("dirLight.specular", light_material.specular*light->color);
		m_Shader->SetVec3("dirLight.direction", light->direction);
	}*/
}