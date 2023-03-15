#include"GLMaterial.h"
namespace EulerEngine {
	void Material::Draw(Shader shader, int dCnt, EulerDirLight* dLight, int pCnt, EulerPointLight* pLight, int sCnt, EulerSpotLight* sLight) {
		bindTexture(shader);
		shader.setInt("dirLightCnt", dCnt);
		shader.setInt("pointLightCnt", pCnt);
		shader.setInt("spotLightCnt", sCnt);
		if (dLight != nullptr) setDirLightRender(shader, dLight);
		if (sLight != nullptr) setSpotLightRender(shader, sLight);
		if (pLight != nullptr) setPointLightRender(shader, pLight);
	}
	void Material::addTexture(Texture2D texture, TextureType type) {
		textures.push_back(texture);
		textures_type.push_back(type);
	}
	void Material::bindTexture(Shader shader) {
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			std::string number;
			TextureType type = textures_type[i];
			if (type == DIFFUSE) {
				number = std::to_string(diffuseNr++);
				shader.setInt(("material.diffuseTex" + number).c_str(), i);
			}
			else if (type == SPECULAR) {
				number = std::to_string(specularNr++);
				shader.setInt(("material.specularTex" + number).c_str(), i);
			}
			glBindTexture(GL_TEXTURE_2D, textures[i].ID);
		}
		shader.setFloat("material.reflectStrength", light_material.reflectStrength);
		glActiveTexture(GL_TEXTURE0);
	}
	void Material::setSpotLightRender(Shader shader, EulerSpotLight* light) {
		shader.setVec3("spotLight.ambient", light_material.ambient*light->color);
		shader.setVec3("spotLight.diffuse", light_material.diffuse*light->color);
		shader.setVec3("spotLight.specular", light_material.specular*light->color);

		shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(light->outerCutOff)));
		shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(light->cutOff)));
		shader.setVec3("spotLight.direction", light->direction);
		shader.setVec3("spotLight.position", light->transform.position);

		shader.setFloat("spotLight.constant", light->constant);
		shader.setFloat("spotLight.linear", light->linear);
		shader.setFloat("spotLight.quatratic", light->quatratic);
	}
	void Material::setPointLightRender(Shader shader, EulerPointLight* light) {
		shader.setVec3("pointLight.position", light->transform.position);
		shader.setVec3("pointLight.ambient", light_material.ambient*light->color);
		shader.setVec3("pointLight.diffuse", light_material.diffuse*light->color);
		shader.setVec3("pointLight.specular", light_material.specular*light->color);

		shader.setFloat("pointLight.constant", light->constant);
		shader.setFloat("pointLight.linear", light->linear);
		shader.setFloat("pointLight.quatratic", light->quatratic);
	}
	void Material::setDirLightRender(Shader shader, EulerDirLight* light) {
		shader.setVec3("dirLight.ambient", light_material.ambient*light->color);
		shader.setVec3("dirLight.diffuse", light_material.diffuse*light->color);
		shader.setVec3("dirLight.specular", light_material.specular*light->color);
		shader.setVec3("dirLight.direction", light->direction);
	}
}