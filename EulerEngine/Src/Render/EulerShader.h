#pragma once
#include<string>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"glad/glad.h"
namespace EulerEngine {
	enum CompileShaderType {
		EULER_VERTEX,
		EULER_FRAGMENT,
		EULER_GEOMETRY,
		EULER_LINK_PROGRAM,
	};
	class EulerShader {
	public:
		EulerShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~EulerShader();

		void Bind() const;
		void Unbind() const;

		//uniform¹¤¾ßº¯Êý;
		void setBool(const std::string& name, bool value) const {
			glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), (int)value);
		}
		void setInt(const std::string& name, int value) const {
			glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
		}
		void setFloat(const std::string& name, float value) const {
			glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
		}
		void setMat3(const std::string& name, glm::mat3 value) const {
			glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
		}
		void setMat4(const std::string& name, glm::mat4 value) const {
			glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
		}
		void setVec2(const std::string& name, float x, float y) const {
			glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), x, y);
		}
		void setVec2(const std::string& name, glm::vec2 value) const {
			glUniform2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
		}
		void setVec3(const std::string& name, float x, float y, float z) const {
			glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z);
		}
		void setVec3(const std::string& name, glm::vec3 value) const {
			glUniform3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
		}
		void setVec4(const std::string& name, float x, float y, float z, float w) const {
			glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z, w);
		}
		void setVec4(const std::string& name, glm::vec4 value) const {
			glUniform4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
		}
	private:
		void CompileShader(const char* Code, unsigned int& shader, CompileShaderType type);
		void CheckError(unsigned int object, unsigned int type);
	private:
		unsigned int m_RendererID;

	};
}