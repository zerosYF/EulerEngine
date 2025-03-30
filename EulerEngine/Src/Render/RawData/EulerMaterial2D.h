#pragma once
#include"Render/EulerShader.h"
#include"Render/RawData/EulerTexture.h"
#include"Render/RawData/EulerMaterial.h"
namespace EulerEngine {
	class EulerMaterial2D: public EulerMaterial{
	private:
		Ref<EulerShader> m_Shader;
		Ref<Texture2D> m_Texture;
		std::unordered_map<std::string, float> m_Paramters;
		glm::vec4 m_Color;

	public:
		EulerMaterial2D();
		void SetShader(Ref<EulerShader> shader) override;
		void SetTexture(Ref<Texture2D> texture) override;
		void SetColor(glm::vec4 color);
		void AddFloatParam(std::string& name, float param);

		Ref<EulerShader>& GetShader() override;
		Ref<Texture2D>& GetTexture() override;
		glm::vec4& GetColor();
		float GetFloatParam(const std::string& name) const;
		void Apply(int texture_slot_index = 0) const;
	};
}