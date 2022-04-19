#pragma once
#ifndef  TEXTURE_H
#define TEXTURE_H
#include<glfw/glfw3.h>
class Texture2D {
public:
	unsigned int ID;
	unsigned int Width, Height;
	unsigned int Interval_Format;
	unsigned int Image_Format;
	unsigned int Wrap_S;
	unsigned int Wrap_T;
	//环绕方式；
	unsigned int Filter_MIN; //缩小过滤方式；
	unsigned int Filter_MAX;//放大过滤方式；

	Texture2D():Width(0),Height(0),
		Interval_Format(GL_RGB),Image_Format(GL_RGB),Wrap_S(GL_REPEAT),Wrap_T(GL_REPEAT),
		Filter_MIN(GL_LINEAR),Filter_MAX(GL_LINEAR){
		glGenTextures(1,	&ID);
	}
	void generate(unsigned int width,unsigned int height,GLenum format,const unsigned char* data) {
		Width = width;
		Height = height;
		Interval_Format = format;
		Image_Format = format;
		glBindTexture(GL_TEXTURE_2D,ID);
		glTexImage2D(GL_TEXTURE_2D,0,Interval_Format,Width,Height,0,Image_Format,GL_UNSIGNED_BYTE,data);
		config();
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,0);
	}
	void config() {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_MIN);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_MAX);
	}
	void bind() const {
		glBindTexture(GL_TEXTURE_2D,ID);
	}
};

#endif
