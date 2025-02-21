#pragma once
#include"EulerTexture.h"
#include"EulerShader.h"
#include<array>
namespace EulerEngine {

	class EulerMaterial {
	private:
		Ref<EulerShader> m_Shader;
		Ref<Texture2D> m_Texture;
		std::unordered_map<std::string, float> m_Paramters;
		glm::vec4 m_Color;


	public:
		EulerMaterial();
		void SetShader(Ref<EulerShader> shader);
		void SetTexture(Ref<Texture2D> texture);
		void SetColor(glm::vec4 color);
		void AddFloatParam(std::string& name, float param);

		Ref<EulerShader> GetShader() const;
		glm::vec4& GetColor();
		Ref<Texture2D>& GetTexture();
		float GetFloatParam(const std::string& name) const;
		void Apply(int texture_slot) const;
		static Ref<EulerMaterial> Create();
	};
}