#pragma once
#include"glm/glm.hpp"
#include"EulerTexture.h"
namespace EulerEngine {
	class SubTexture2D {
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
		~SubTexture2D() = default;
		const Ref<Texture2D>& GetTexture() const { return m_Texture; }
		const glm::vec2* GetTexCoords() { return m_TexCoords; }

		static Ref<SubTexture2D> CreateFromCoords(const glm::vec2& coords, const glm::vec2& cellSize, const Ref<Texture2D>& texture);
	private:
		Ref<Texture2D> m_Texture;
		glm::vec2 m_Min;
		glm::vec2 m_Max;
		glm::vec2 m_TexCoords[4];
	};
}