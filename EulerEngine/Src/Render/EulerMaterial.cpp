#include "gkpch.h"
#include"EulerMaterial.h"
namespace EulerEngine {
	void Material::Draw(int dCnt, EulerDirLight* dLight, int pCnt, EulerPointLight* pLight, int sCnt, EulerSpotLight* sLight) {
		bindTexture();
		m_Shader.setInt("dirLightCnt", dCnt);
		m_Shader.setInt("pointLightCnt", pCnt);
		m_Shader.setInt("spotLightCnt", sCnt);
		if (dLight != nullptr) setDirLightRender(dLight);
		if (sLight != nullptr) setSpotLightRender(sLight);
		if (pLight != nullptr) setPointLightRender(pLight);
	}
	void Material::addTexture(std::shared_ptr<Texture2D> texture, TextureType type) {
		textures.push_back(texture);
		textures_type.push_back(type);
	}
	void Material::bindTexture() {
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			std::string number;
			TextureType type = textures_type[i];
			if (type == DIFFUSE) {
				number = std::to_string(diffuseNr++);
				m_Shader.setInt(("material.diffuseTex" + number).c_str(), i);
			}
			else if (type == SPECULAR) {
				number = std::to_string(specularNr++);
				m_Shader.setInt(("material.specularTex" + number).c_str(), i);
			}
			glBindTexture(GL_TEXTURE_2D, textures[i].ID);
		}
		m_Shader.setFloat("material.reflectStrength", light_material.reflectStrength);
		glActiveTexture(GL_TEXTURE0);
	}
	void Material::setSpotLightRender(EulerSpotLight* light) {
		m_Shader.setVec3("spotLight.ambient", light_material.ambient*light->color);
		m_Shader.setVec3("spotLight.diffuse", light_material.diffuse*light->color);
		m_Shader.setVec3("spotLight.specular", light_material.specular*light->color);
		m_Shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(light->outerCutOff)));
		m_Shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(light->cutOff)));
		m_Shader.setVec3("spotLight.direction", light->direction);
		m_Shader.setVec3("spotLight.position", light->transform.position);
		m_Shader.setFloat("spotLight.constant", light->constant);
		m_Shader.setFloat("spotLight.linear", light->linear);
		m_Shader.setFloat("spotLight.quatratic", light->quatratic);
	}
	void Material::setPointLightRender(EulerPointLight* light) {
		m_Shader.setVec3("pointLight.position", light->transform.position);
		m_Shader.setVec3("pointLight.ambient", light_material.ambient*light->color);
		m_Shader.setVec3("pointLight.diffuse", light_material.diffuse*light->color);
		m_Shader.setVec3("pointLight.specular", light_material.specular*light->color);
		m_Shader.setFloat("pointLight.constant", light->constant);
		m_Shader.setFloat("pointLight.linear", light->linear);
		m_Shader.setFloat("pointLight.quatratic", light->quatratic);
	}
	void Material::setDirLightRender(EulerDirLight* light) {
		m_Shader.setVec3("dirLight.ambient", light_material.ambient*light->color);
		m_Shader.setVec3("dirLight.diffuse", light_material.diffuse*light->color);
		m_Shader.setVec3("dirLight.specular", light_material.specular*light->color);
		m_Shader.setVec3("dirLight.direction", light->direction);
	}
}