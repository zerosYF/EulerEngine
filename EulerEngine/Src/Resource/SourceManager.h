#pragma once
#ifndef  RESOURCE_MGR
#define RESOURCE_MGR
#include<map>
#include<string.h>
//#include<GLFW/glfw3.h>
//#include"../Render/OpenGL/GLShader.h"
//#include"../Render/OpenGL/GLTexture.h"
//#include "../Utils/stb_image.h"
//#include<iostream>
//#include<filesystem>
//#include<vector>
//namespace EulerEngine {
//	
//	class SourceManager {
//	private:
//		std::map<std::string, Shader> shaders;
//		std::map<std::string, Texture2D> textures;
//	public:
//		void Initialize() {
//		}
//
//
//		Shader loadShader(std::string name,const char* vShaderFile, const char* fShaderFile) {
//			shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
//			return shaders[name];
//		}
//		Shader getShader(std::string name) {
//			return shaders[name];
//		}
//		Texture2D loadTexture(const char* file, std::string name) {
//			textures[name] = loadTextureFromFile(file,name);
//			return textures[name];
//		}
//		Texture2D getTexture(std::string name) {
//			return textures[name];
//		}
//		bool hasTexture(std::string name) {
//			return textures.find(name) != textures.end();
//		}
//		void Clear() {
//			for (auto &it : shaders) {
//				glDeleteProgram(it.second.GetID());
//			}
//			for (auto &it : textures) {
//				glDeleteTextures(1, &it.second.ID);
//			}
//		}
//	private:
//		Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile) {
//			std::string vertexCode;
//			std::string fragmentCode;
//			std::string geometryCode;
//			std::ifstream vertexShaderFile;
//			std::ifstream fragmentShaderFile;
//			std::ifstream geometryShaderFile;
//			// 抛出异常;
//			vertexShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
//			fragmentShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
//			geometryShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
//			try {
//				vertexShaderFile.open(vShaderFile);
//				fragmentShaderFile.open(fShaderFile);
//				std::stringstream vertexShaderStream, fragmentShaderStream;
//				vertexShaderStream << vertexShaderFile.rdbuf();
//				fragmentShaderStream << fragmentShaderFile.rdbuf();
//				vertexCode = vertexShaderStream.str();
//				fragmentCode = fragmentShaderStream.str();
//			}
//			catch (std::ifstream::failure e) {
//				std::cout << "Read File Failed" << std::endl;
//			}
//			const char* vCode = vertexCode.c_str();
//			const char* fCode = fragmentCode.c_str();
//			const char* gCode = geometryCode.c_str();
//			Shader shader;
//			shader.compile(vCode, fCode);
//			return shader;
//		}
//		Texture2D loadTextureFromFile(const char* file, std::string name) {
//			Texture2D texture2D(name);
//			int width, height;
//			int Channel_cnt;
//			stbi_set_flip_vertically_on_load(true);
//			unsigned char* data = 0;
//			data = stbi_load(file, &width, &height, &Channel_cnt, 0);
//			if (data) {
//				GLenum format = GL_RGB;
//				if (Channel_cnt == 1) {
//					format = GL_RED;
//				}
//				else if (Channel_cnt == 3) {
//					format = GL_RGB;
//				}
//				else if (Channel_cnt == 4) {
//					format = GL_RGBA;
//				}
//				texture2D.generate(width, height, format, data);
//			}
//			else {
//				std::cout << "创建纹理失败,大概率文件有问题" << std::endl;
//			}
//			stbi_image_free(data);
//			return texture2D;
//		}
//	};
//}
#endif