#include "gkpch.h"
#include"EulerMaterial.h"
namespace EulerEngine {
	void Material::Draw(int dCnt, EulerDirLight* dLight, int pCnt, EulerPointLight* pLight, int sCnt, EulerSpotLight* sLight) {
		bindTexture();
		m_Shader->SetInt("dirLightCnt", dCnt);
		m_Shader->SetInt("pointLightCnt", pCnt);
		m_Shader->SetInt("spotLightCnt", sCnt);
		if (dLight != nullptr) setDirLightRender(dLight);
		if (sLight != nullptr) setSpotLightRender(sLight);
		if (pLight != nullptr) setPointLightRender(pLight);
	}
	void Material::addTexture(std::string texture_path, TextureType type) {
		Ref<Texture2D> new_texture =  Texture2D::Create(texture_path, type);
		textures.push_back(new_texture);
	}
	void Material::bindTexture() {
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			std::string number;
			TextureType type = textures[i]->GetType();
			if (type == DIFFUSE) {
				number = std::to_string(diffuseNr++);
				m_Shader->SetInt(("material.diffuseTex" + number).c_str(), i);
			}
			else if (type == SPECULAR) {
				number = std::to_string(specularNr++);
				m_Shader->SetInt(("material.specularTex" + number).c_str(), i);
			}
			glBindTexture(GL_TEXTURE_2D, textures[i].RendererID);
		}
		m_Shader->SetFloat("material.reflectStrength", light_material.reflectStrength);
		glActiveTexture(GL_TEXTURE0);
	}
	void Material::setSpotLightRender(EulerSpotLight* light) {
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
	}
}