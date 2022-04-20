#pragma once
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<string.h>
#include<iostream>
using namespace std;
GLenum glCheckError(const char *file,int line) {
	GLenum errcode;
	while ((errcode==glGetError())!=GL_NO_ERROR) {
		string error;
		switch (errcode)
		{
		case GL_INVALID_ENUM: error = "��Ч��ö��"; break;
		case GL_INVALID_VALUE:error = "��Ч��ֵ"; break;
		case GL_INVALID_OPERATION:error = "��Ч�Ĳ���"; break;
		case GL_STACK_OVERFLOW:error = "ջ���"; break;
		case GL_STACK_UNDERFLOW: error = "�����"; break;
		case GL_OUT_OF_MEMORY:error = "�ڴ治��"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "��Ч֡�������"; break;
		}
		cout <<"�������:"<<errcode<< "��������:"<<error.c_str() <<file<<"("<<line<<")"<< endl;
	}
	return errcode;
}
#define glCheckError() glCheckError(__FILE__,__LINE__)
