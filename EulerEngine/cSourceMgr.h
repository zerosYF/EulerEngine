#pragma once
#ifndef  RESOURCE_MGR
#define RESOURCE_MGR
#include<map>
#include<string.h>
#include<GLFW/glfw3.h>
#include"cShader.h"
#include"cTexture.h"
#include "stb_image.h"
using namespace std;
class SourceManager {
public:
	static map<string, Shader> shaders;
	static map<string, Texture2D> textures;
	static Shader loadShader(const char* vShaderFile,const char* fShaderFile,const char* gShaderFile,string name) {
		shaders[name] = loadShaderFromFile(vShaderFile,fShaderFile,gShaderFile);
		return shaders[name];
	}
	static Shader getShader(string name) {
		return shaders[name];
	}
	static Texture2D loadTexture(const char* file,bool alpha,string name) {
		textures[name] = loadTextureFromFile(file);
		return textures[name];
	}
	static Texture2D getTexture(string name) {
		return textures[name];
	}
	static void Clear() {
		for (auto &it : shaders) {
			glDeleteProgram(it.second.ID);
		}
		for (auto &it : textures) {
			glDeleteTextures(1,&it.second.ID);
		}
	}
private:
	SourceManager() {}
	static Shader loadShaderFromFile(const char* vShaderFile,const char* fShaderFile,const char* gShaderFile=nullptr) {
		string vertexCode;
		string fragmentCode;
		string geometryCode;
		ifstream vertexShaderFile;
		ifstream fragmentShaderFile;
		ifstream geometryShaderFile;
		// 抛出异常;
		vertexShaderFile.exceptions(ifstream::badbit | ifstream::failbit);
		fragmentShaderFile.exceptions(ifstream::badbit | ifstream::failbit);
		geometryShaderFile.exceptions(ifstream::badbit | ifstream::failbit);
		try {
			vertexShaderFile.open(vShaderFile);
			fragmentShaderFile.open(fShaderFile);
			stringstream vertexShaderStream, fragmentShaderStream;
			vertexShaderStream << vertexShaderFile.rdbuf();
			fragmentShaderStream << fragmentShaderFile.rdbuf();
			vertexCode = vertexShaderStream.str();
			fragmentCode = fragmentShaderStream.str();

			if (gShaderFile != nullptr) {
				geometryShaderFile.open(gShaderFile);
				stringstream geometryStream;
				geometryStream << geometryShaderFile.rdbuf();
				geometryCode = geometryStream.str();
			}
		}
		catch (ifstream::failure e) {
			cout << "Read File Failed" << endl;
		}
		const char* vCode = vertexCode.c_str();
		const char* fCode = fragmentCode.c_str();
		const char* gCode = geometryCode.c_str();
		Shader shader;
		shader.compile(vCode,fCode,gCode!=nullptr?gCode:nullptr);
		return shader;
	}
	static Texture2D loadTextureFromFile(const char* file) {
		Texture2D texture2D;
		int width, height;
		int nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = 0;
		data = stbi_load(file, &width, &height, &nrChannels,0);
		if (data) {
			GLenum format = GL_RGB;
			if (nrChannels == 1) {
				format = GL_RED;
			}
			else if (nrChannels == 3) {
				format = GL_RGB;
			}
			else if (nrChannels == 4) {
				format = GL_RGBA;
			}
			texture2D.generate(width, height, format,data);
		}
		else {
			cout << "创建纹理失败,大概率文件有问题" << std::endl;
		}
		stbi_image_free(data);
		return texture2D;
	}
};
#endif