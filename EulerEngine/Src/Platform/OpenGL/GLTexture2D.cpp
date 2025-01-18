#include"gkpch.h"
#include"GLTexture2D.h"
#include"stb_image/stb_image.h"
#include"glad/glad.h"
namespace EulerEngine {
	OpenGLTexture2D::OpenGLTexture2D(std::string path) {
		int width, height, channels;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 4);
		Width = width;
		Height = height;
		GLenum internal_format = 0;
		GLenum data_format = 0;
		if (data) {
			GLenum format = GL_RGB;
			if (channels == 1) {
				format = GL_RED;
			}
			else if (channels == 3) {
				format = GL_RGB;

			}
			else if (channels == 4) {
				format = GL_RGBA;
			}
			generate(width, height, format, data);
		}
		glGenTextures(GL_TEXTURE_2D, &ID);
		
	}
	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &ID);
	}
	void OpenGLTexture2D::Bind(unsigned int slot) const
	{
		glBindTexture(slot, ID);
	}
}