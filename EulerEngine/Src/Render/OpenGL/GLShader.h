#pragma once
#ifndef SHADER_H
#define SHADER_H
//#include<glad/glad.h>
//#include<string>
//#include<iostream>
//#include<sstream>
//#include<fstream>
//#include"../../Math/EulerMath.h"
//class Shader 
//{
//private:
//	enum CompileShaderType {
//		EULER_VERTEX,
//		EULER_FRAGMENT,
//		EULER_GEOMETRY,
//		EULER_LINK_PROGRAM,
//	};
//	unsigned int ID;
//public:
//	Shader() {}
//	void use() {
//		glUseProgram(ID);
//	}
//	unsigned int GetID() {
//		return ID;
//	}
//	//uniform工具函数;
//	void setBool(const std::string &name, bool value) const {
//		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
//	}
//	void setInt(const std::string &name, int value) const {
//		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
//	}
//	void setFloat(const std::string &name, float value) const {
//		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
//	}
//	void setMat3(const std::string &name, glm::mat3 value) const {
//		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
//	}
//	void setMat4(const std::string &name,glm::mat4 value) const {
//		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
//	}
//	void setVec2(const std::string &name,float x,float y) const{
//		glUniform2f(glGetUniformLocation(ID,name.c_str()),x,y);
//	}
//	void setVec2(const std::string &name,glm::vec2 value) const{
//		glUniform2fv(glGetUniformLocation(ID,name.c_str()),1,glm::value_ptr(value));
//	}
//	void setVec3(const std::string &name, float x, float y, float z) const {
//		glUniform3f(glGetUniformLocation(ID, name.c_str()),x,y,z);
//	}
//	void setVec3(const std::string &name,glm::vec3 value) const{
//		glUniform3fv(glGetUniformLocation(ID,name.c_str()),1,glm::value_ptr(value));
//	}
//	void setVec4(const std::string &name,float x,float y,float z,float w) const{
//		glUniform4f(glGetUniformLocation(ID,name.c_str()),x,y,z,w);
//	}
//	void setVec4(const std::string &name,glm::vec4 value) const{
//		glUniform4fv(glGetUniformLocation(ID,name.c_str()),1,glm::value_ptr(value));
//	}
//	~Shader() {
//		//析构该干点啥呢。
//	}
//};
#endif // !SHADER_H