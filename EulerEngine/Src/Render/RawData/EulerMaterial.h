#pragma once
#include"EulerTexture.h"
#include"Render/EulerShader.h"
#include<array>
namespace EulerEngine {

	class EulerMaterial {
	private:
		Ref<EulerShader> m_Shader;
		Ref<Texture2D> m_Texture;
		std::unordered_map<std::string, float> m_Paramters;
		glm::vec3 m_Albedo;
		float m_Roughness;

	public:
		EulerMaterial();
		void SetShader(Ref<EulerShader> shader);
		void SetTexture(Ref<Texture2D> texture);
		void SetAlbedo(glm::vec3 albedo);
		void SetRoughness(float roughness);
		void AddFloatParam(std::string& name, float param);

		Ref<EulerShader>& GetShader();
		Ref<Texture2D>& GetTexture();
		glm::vec3& GetAlbedo();
		float& GetRoughness();
		float GetFloatParam(const std::string& name) const;
		void Apply(int texture_slot_index = 0) const;
	};
}