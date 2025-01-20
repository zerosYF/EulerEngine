#include"gkpch.h"
#include"GLTexture2D.h"
#include"stb_image/stb_image.h"
#include"glad/glad.h"
namespace EulerEngine {
	OpenGLTexture2D::OpenGLTexture2D(std::string path, TextureType type) {
		m_Wrap_S = GL_REPEAT;
		m_Wrap_T = GL_REPEAT;
		m_Filter_MIN = GL_LINEAR;
		m_Filter_MAX = GL_LINEAR;
		m_RendererID = 0;
		m_Internal_Format = 0;
		m_Data_Format = 0;
		this->m_Path = path;
		this->m_Type = type;
		stbi_uc* data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 4);
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
			glGenTextures(GL_TEXTURE_2D, &m_RendererID);
			glBindTexture(GL_TEXTURE_2D, m_RendererID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->m_Wrap_S);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->m_Wrap_T);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->m_Filter_MIN);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->m_Filter_MAX);
			glTexImage2D(GL_TEXTURE_2D, 0, m_Internal_Format, m_Width, m_Height, 0, m_Data_Format, GL_UNSIGNED_BYTE, data);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_Data_Format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(data);
		}
	}
	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture2D::Bind(unsigned int slot) const
	{
		glBindTexture(slot, m_RendererID);
	}
}