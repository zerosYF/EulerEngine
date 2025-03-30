#pragma once
#include"EulerTexture.h"
#include"Render/EulerShader.h"
#include<array>
namespace EulerEngine {
	class EulerMaterial {
	public:
		virtual void SetShader(Ref<EulerShader> shader) = 0;
		virtual void SetTexture(Ref<Texture2D> texture) = 0;
		virtual Ref<EulerShader>& GetShader() = 0;
		virtual Ref<Texture2D>& GetTexture() = 0;
	};

	class EulerMaterial3D: public EulerMaterial {
	private:
		Ref<EulerShader> m_Shader;
		Ref<Texture2D> m_Texture;
		std::unordered_map<std::string, float> m_Paramters;
		glm::vec3 m_Albedo;
		float m_Roughness;

	public:
		EulerMaterial3D();
		void SetShader(Ref<EulerShader> shader) override;
		void SetTexture(Ref<Texture2D> texture) override;
		void SetAlbedo(glm::vec3 albedo);
		void SetRoughness(float roughness);
		void AddFloatParam(std::string& name, float param);

		Ref<EulerShader>& GetShader() override;
		Ref<Texture2D>& GetTexture() override;
		glm::vec3& GetAlbedo();
		float& GetRoughness();
		float GetFloatParam(const std::string& name) const;
		void Apply(int texture_slot_index = 0) const;
	};
}