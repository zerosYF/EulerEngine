#pragma once
#ifndef SHADER_H
#define SHADER_H
#include<glad/glad.h>
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include"../../Math/EulerMath.h"
class Shader 
{
private:
	enum CompileShaderType {
		EULER_VERTEX,
		EULER_FRAGMENT,
		EULER_GEOMETRY,
		EULER_LINK_PROGRAM,
	};
	unsigned int ID;
public:
	Shader() {}
	void compile(const char*vertexCode,const char*fragmentCode) {
		unsigned int vertexShader, fragmentShader;
		CompileShader(vertexCode,vertexShader,EULER_VERTEX);
		CompileShader(fragmentCode, fragmentShader, EULER_FRAGMENT);

		ID = glCreateProgram();
		std::cout << "程序ID：" << ID << std::endl;
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);

		glLinkProgram(ID);
		checkError(ID,EULER_LINK_PROGRAM);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	void use() {
		glUseProgram(ID);
	}
	unsigned int GetID() {
		return ID;
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
	void setMat3(const std::string &name, glm::mat3 value) const {
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
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
	void CompileShader(const char*Code,unsigned int& shader,CompileShaderType type) {
		if(type==EULER_VERTEX)
			shader = glCreateShader(GL_VERTEX_SHADER);
		else if (type == EULER_FRAGMENT) 
			shader = glCreateShader(GL_FRAGMENT_SHADER);
		else
			shader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(shader, 1, &Code, NULL);
		glCompileShader(shader);
		checkError(shader, type);
	}
	void checkError(unsigned int object,unsigned int type) {
		int success;
		char infoLog[512];
		if (type != EULER_LINK_PROGRAM) {
			glGetShaderiv(object,GL_COMPILE_STATUS,&success);
			if (!success) {
				std::string t;
				if (type == EULER_VERTEX) t = "顶点shader";
				else if (type == EULER_FRAGMENT) t = "片段shader";
				else if (type == EULER_GEOMETRY) t = "几何shader";

				glGetShaderInfoLog(object,512,NULL,infoLog);
				std::cout<<t<<"编译失败\n"<<"log: "<<infoLog<< std::endl;
			}
		}
		else {
			glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(object,512,NULL,infoLog);
				std::cout << "链接失败\n" <<"log: "<<infoLog<< std::endl;
			}
		}
	}
};
#endif // !SHADER_H