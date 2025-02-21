#include"gkpch.h"
#include"GLTexture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image/stb_image.h"
#include"glad/glad.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	OpenGLTexture2D::OpenGLTexture2D(unsigned int width, unsigned int height)
	{
		m_Wrap_S = GL_REPEAT;
		m_Wrap_T = GL_REPEAT;
		m_Filter_MIN = GL_LINEAR;
		m_Filter_MAX = GL_LINEAR;
		m_RendererID = 0;
		m_Internal_Format = 0;
		m_Data_Format = 0;
		
		m_Internal_Format = GL_RGBA;
		m_Data_Format = GL_RGBA;

		m_Width = width;
		m_Height = height;
		m_Channels = 4;

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexImage2D(GL_TEXTURE_2D, 0, m_Internal_Format, m_Width, m_Height, 0, m_Data_Format, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->m_Wrap_S);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->m_Wrap_T);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_Filter_MIN);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_Filter_MAX);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		KINK_CORE_INFO("Texture load success... ID:{0}", m_RendererID);
	}
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) {
		m_Wrap_S = GL_REPEAT;
		m_Wrap_T = GL_REPEAT;
		m_Filter_MIN = GL_LINEAR;
		m_Filter_MAX = GL_LINEAR;
		m_RendererID = 0;
		m_Internal_Format = 0;
		m_Data_Format = 0;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);
		if (data) {
			if (m_Channels == 1) {
				m_Internal_Format = GL_RED;
				m_Data_Format = GL_RED;
			}
			else if (m_Channels == 3) {
				m_Internal_Format = GL_RGB;
				m_Data_Format = GL_RGB;

			}
			else if (m_Channels == 4) {
				m_Internal_Format = GL_RGBA;
				m_Data_Format = GL_RGBA;
			}

			glGenTextures(1, &m_RendererID);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);
			glTexImage2D(GL_TEXTURE_2D, 0, m_Internal_Format, m_Width, m_Height, 0, m_Data_Format, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->m_Wrap_S);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->m_Wrap_T);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_Filter_MIN);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_Filter_MAX);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
			KINK_CORE_INFO("Texture load success...ID:{0}", m_RendererID);
		}
		else {
			KINK_CORE_ERROR("NO DATA FROM IMAGE");
		}
		stbi_image_free(data);
	}
	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture2D::SetData(void* data, unsigned int size)
	{
		unsigned int bpp = m_Data_Format == GL_RGBA ? 4 : 3;
		KINK_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_Data_Format, GL_UNSIGNED_BYTE, data);
	}
	void OpenGLTexture2D::Bind(unsigned int slot) const
	{
		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
	bool OpenGLTexture2D::operator==(const Texture& another) const
	{
		return m_RendererID == ((OpenGLTexture2D&)another).m_RendererID;
	}
}