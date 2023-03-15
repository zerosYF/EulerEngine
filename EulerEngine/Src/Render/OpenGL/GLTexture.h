#pragma once
#include<iostream>
#ifndef  TEXTURE_H
#define TEXTURE_H
#include<glfw/glfw3.h>
#include<glad/glad.h>
#include<string>
namespace EulerEngine {
	enum TextureType {
		DIFFUSE,
		SPECULAR,
	};
	class Texture2D {
	public:
		unsigned int ID;
		std::string name;
		unsigned int Width, Height;
		unsigned int Save_Format;
		unsigned int Image_Format;
		unsigned int Wrap_S;
		unsigned int Wrap_T;
		//环绕方式；
		unsigned int Filter_MIN; //缩小过滤方式；
		unsigned int Filter_MAX;//放大过滤方式；
		Texture2D() :ID(0), Width(0), Height(0),
			Save_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT),
			Filter_MIN(GL_LINEAR), Filter_MAX(GL_LINEAR) {
		}
		Texture2D(std::string name) :ID(0),Width(0), Height(0),
			Save_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT),
			Filter_MIN(GL_LINEAR), Filter_MAX(GL_LINEAR) {
			this->name = name;
		}
		void generate(unsigned int width, unsigned int height, GLenum format, const unsigned char* data) {
			Width = width;
			Height = height;
			Save_Format = format;
			Image_Format = format;
			glGenTextures(1, &ID);
			std::cout << "纹理ID：" << ID <<"  纹理名称: "<<name<< std::endl;
			glBindTexture(GL_TEXTURE_2D, ID);
			config();
			glTexImage2D(GL_TEXTURE_2D, 0, Save_Format, Width, Height, 0, Image_Format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		void config() {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_MIN);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_MAX);
		}
	};
}
#endif
