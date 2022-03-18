#pragma once
#ifndef SHADER_H
#define SHADER_H
#include<glad/glad.h>
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
class Shader 
{
public:
	unsigned int ID;
	Shader() {}
	void compile(const char*vertexCode,const char*fragmentCode,const char*geometryCode=nullptr) {
		unsigned int vertexShader, fragmentShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexCode, NULL);
		glCompileShader(vertexShader);
		checkError(vertexShader, "Vertex");

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
		glCompileShader(fragmentShader);
		checkError(fragmentShader, "Fragment");

		unsigned int geometryShader;
		if (geometryCode != nullptr) {
			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometryShader, 1, &geometryCode, NULL);
			glCompileShader(geometryShader);
			checkError(geometryShader, "Geometry");
		}
		ID = glCreateProgram();
		cout << "ID" << ID << endl;
		glAttachShader(ID, vertexShader);
		if (geometryCode != nullptr) {
			glAttachShader(ID, geometryShader);
		}
		glAttachShader(ID, fragmentShader);

		glLinkProgram(ID);
		checkError(ID, "Program");
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (geometryCode != nullptr) {
			glDeleteShader(geometryShader);
		}
	}
	void use() {
		glUseProgram(ID);
	}
	//uniform工具函数;
	void setBool(const std::string &name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string &name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string &name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setMat4(const std::string &name,glm::mat4 value) const {
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}
	void setVec2(const std::string &name,float x,float y) const{
		glUniform2f(glGetUniformLocation(ID,name.c_str()),x,y);
	}
	void setVec2(const std::string &name,glm::vec2 value) const{
		glUniform2fv(glGetUniformLocation(ID,name.c_str()),1,glm::value_ptr(value));
	}
	void setVec3(const std::string &name, float x, float y, float z) const {
		glUniform3f(glGetUniformLocation(ID, name.c_str()),x,y,z);
	}
	void setVec3(const std::string &name,glm::vec3 value) const{
		glUniform3fv(glGetUniformLocation(ID,name.c_str()),1,glm::value_ptr(value));
	}
	void setVec4(const std::string &name,float x,float y,float z,float w) const{
		glUniform4f(glGetUniformLocation(ID,name.c_str()),x,y,z,w);
	}
	void setVec4(const std::string &name,glm::vec4 value) const{
		glUniform4fv(glGetUniformLocation(ID,name.c_str()),1,glm::value_ptr(value));
	}
	~Shader() {
		//析构该干点啥呢。
	}
private:
	void checkError(unsigned int object,string type) {
		int success;
		char infoLog[512];
		if (type != "Program") {
			glGetShaderiv(object,GL_COMPILE_STATUS,&success);
			if (!success) {
				glGetShaderInfoLog(object,512,NULL,infoLog);
				cout<<type<<"编译失败\n"
					<<"log: "<<infoLog<<endl;
			}
		}
		else {
			glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(object,512,NULL,infoLog);
				cout << type << "链接失败\n" 
					<<"log: "<<infoLog<< endl;
			}
		}
	}
};
#endif // !SHADER_H