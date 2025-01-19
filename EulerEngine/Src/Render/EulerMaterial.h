#pragma once
#include"EulerTexture.h"
#include"GLObjects/GLLight.h"
#include"EulerShader.h"
#include<vector>
namespace EulerEngine {

	struct LightMaterial {
		float ambient{0.1f};
		float diffuse{0.5f};
		float specular{1.0f};
		float reflectStrength{32};
	};

	class EulerDirLight;
	class EulerSpotLight;
	class EulerPointLight;

	class Material {
	private:
		std::vector<Texture2D> textures;
		std::vector<TextureType> textures_type;
		LightMaterial light_material;
		glm::vec4 m_Color;
		std::shared_ptr<EulerShader> m_Shader;
	public:
		Material(std::shared_ptr<EulerShader> shader):m_Shader(shader) {}
		void Draw(int dCnt, EulerDirLight* dLight, int pCnt, EulerPointLight* pLight, int sCnt, EulerSpotLight* sLight);
		void addTexture(std::shared_ptr<Texture2D> texture, TextureType type);
		void setColor(glm::vec4 color) { m_Color = color; }
	private:
		void bindTexture();
		void setSpotLightRender(EulerSpotLight* light);
		void setPointLightRender(EulerPointLight* light);
		void setDirLightRender(EulerDirLight* light);
	};
}