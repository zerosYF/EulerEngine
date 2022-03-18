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
		case GL_INVALID_ENUM: error = "无效的枚举"; break;
		case GL_INVALID_VALUE:error = "无效的值"; break;
		case GL_INVALID_OPERATION:error = "无效的操作"; break;
		case GL_STACK_OVERFLOW:error = "栈溢出"; break;
		case GL_STACK_UNDERFLOW: error = "下溢出"; break;
		case GL_OUT_OF_MEMORY:error = "内存不足"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "无效帧缓冲操作"; break;
		}
		cout <<"错误代码:"<<errcode<< "发生错误:"<<error.c_str() <<file<<"("<<line<<")"<< endl;
	}
	return errcode;
}
#define glCheckError() glCheckError(__FILE__,__LINE__)
