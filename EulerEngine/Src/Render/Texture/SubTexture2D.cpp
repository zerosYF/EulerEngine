#include"gkpch.h"
#include"SubTexture2D.h"
namespace EulerEngine {
	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max)
		:m_Texture(texture), m_Min(min), m_Max(max)
	{
		m_TexCoords[0] = { min.x, min.y };
		m_TexCoords[1] = { max.x, min.y };
		m_TexCoords[2] = { max.x, max.y };
		m_TexCoords[3] = { min.x, max.y };
	}
	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const glm::vec2& coords, const glm::vec2& cellSize, const Ref<Texture2D>& texture)
	{
		float sheetWidth = texture->GetWidth(); 
		float sheetHeight = texture->GetHeight();
		float spriteWidth = cellSize.x;
		float spriteHeight = cellSize.y;
		glm::vec2 min = { (coords.x * spriteWidth) / sheetWidth, (coords.y * spriteHeight) / sheetHeight };
		glm::vec2 max = { (coords.x * spriteWidth + spriteWidth) / sheetWidth, (coords.y * spriteHeight + spriteHeight) / sheetHeight };

		return Ref<SubTexture2D>(new SubTexture2D(texture, min, max));
	}
}