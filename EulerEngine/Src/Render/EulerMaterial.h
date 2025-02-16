#pragma once
#include"EulerTexture.h"
#include"EulerShader.h"
#include<array>
namespace EulerEngine {

	class Material {
	private:
		Ref<Texture2D> m_Texture;
		std::unordered_map<std::string, float> m_Paramters;
		glm::vec4 m_Color;


	public:
		Material();
		void SetTexture(Ref<Texture2D> texture);
		void SetColor(glm::vec4 color);
		void AddFloatParam(std::string& name, float param);

		glm::vec4 GetColor() const;
		Ref<Texture2D> GetTexture() const;
		float GetFloatParam(const std::string& name) const;
		void Apply(Ref<EulerShader>& shader, int texture_slot) const;
		static Ref<Material> Create();
	};
}