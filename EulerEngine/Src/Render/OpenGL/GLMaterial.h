#pragma once
#include"GLTexture.h"
#include"../GLObjects/GLLight.h"
#include<vector>
namespace EulerEngine {

	/*struct LightMaterial {
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
	public:
		Material() {}
		void Draw(Shader shader, int dCnt, EulerDirLight* dLight, int pCnt, EulerPointLight* pLight, int sCnt, EulerSpotLight* sLight);
		void addTexture(Texture2D texture, TextureType type);
	private:
		void bindTexture(Shader shader);
		void setSpotLightRender(Shader shader, EulerSpotLight* light);
		void setPointLightRender(Shader shader, EulerPointLight* light);
		void setDirLightRender(Shader shader, EulerDirLight* light);
	};*/
}