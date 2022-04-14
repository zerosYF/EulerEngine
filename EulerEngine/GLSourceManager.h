#pragma once
#ifndef  RESOURCE_MGR
#define RESOURCE_MGR
#include<map>
#include<string.h>
#include<GLFW/glfw3.h>
#include"GLShader.h"
#include"GLTexture.h"
#include "stb_image.h"
using namespace std;
namespace EulerEngine {
	class SourceManager {
	private:
		map<string, Shader> shaders;
		map<string, Texture2D> textures;
		static SourceManager* _instance;
	public:
		static SourceManager* GetInstance() {
			if (_instance == NULL) {
				_instance = new SourceManager();
			}
			return _instance;
		}
		Shader loadShader(string name,const char* vShaderFile, const char* fShaderFile) {
			shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
			return shaders[name];
		}
		Shader getShader(string name) {
			return shaders[name];
		}
		Texture2D loadTexture(const char* file, bool alpha, string name) {
			textures[name] = loadTextureFromFile(file);
			return textures[name];
		}
		Texture2D getTexture(string name) {
			return textures[name];
		}
		void Clear() {
			for (auto &it : shaders) {
				glDeleteProgram(it.second.GetID());
			}
			for (auto &it : textures) {
				glDeleteTextures(1, &it.second.ID);
			}
		}
	private:
		SourceManager() {}
		Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile) {
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
			}
			catch (ifstream::failure e) {
				cout << "Read File Failed" << endl;
			}
			const char* vCode = vertexCode.c_str();
			const char* fCode = fragmentCode.c_str();
			const char* gCode = geometryCode.c_str();
			Shader shader;
			shader.compile(vCode, fCode);
			return shader;
		}
		Texture2D loadTextureFromFile(const char* file) {
			Texture2D texture2D;
			int width, height;
			int nrChannels;
			stbi_set_flip_vertically_on_load(true);
			unsigned char* data = 0;
			data = stbi_load(file, &width, &height, &nrChannels, 0);
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
				texture2D.generate(width, height, format, data);
			}
			else {
				cout << "创建纹理失败,大概率文件有问题" << std::endl;
			}
			stbi_image_free(data);
			return texture2D;
		}
	};
	SourceManager* SourceManager::_instance = NULL;
}
#endif