#pragma once
#include"EulerTexture.h"
#include"EulerShader.h"
namespace EulerEngine {

	class Material {
	private:
		std::unordered_map<std::string, Ref<Texture2D>> m_Textures;
		std::unordered_map<std::string, float> m_Paramters;
		glm::vec4 m_Color;

	public:
		Material();
		void AddTexture(const std::string& name, Ref<Texture2D> texture);
		void SetColor(glm::vec4 color);
		void AddFloatParam(std::string& name, float param);

		Ref<Texture2D> GetTexture(const std::string& name) const;
		glm::vec4 GetColor() const;
		float GetFloatParam(const std::string& name) const;
		void Apply(Ref<EulerShader>& shader) const;
		static Ref<Material> Create();
	};
}