#pragma once
#include<string>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include"Render/EulerShader.h"
namespace EulerEngine {
	enum class ErrorType {
		COMPILE,
		LINK,
	};
	class OpenGLShader:public EulerShader{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& path);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual std::string GetPath() const override;

		//uniform;
		virtual void inline SetBool(const std::string& name, bool value) const override{
			glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), (int)value);
		}
		virtual void inline SetInt(const std::string& name, int value) const override {
			glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
		}
		virtual void inline SetIntArray(const std::string& name, int* values, unsigned int count) const override{
			glUniform1iv(glGetUniformLocation(m_RendererID, name.c_str()), count, values);
		}
		virtual void inline SetFloat(const std::string& name, float value) const override {
			glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
		}
		virtual void inline SetMat3(const std::string& name, glm::mat3 value) const override {
			glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
		}
		virtual void inline SetMat4(const std::string& name, glm::mat4 value) const override {
			glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
		}
		virtual void inline SetVec2(const std::string& name, float x, float y) const override {
			glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), x, y);
		}
		virtual void inline SetVec2(const std::string& name, glm::vec2 value) const override {
			glUniform2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
		}
		virtual void inline SetVec3(const std::string& name, float x, float y, float z) const override {
			glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z);
		}
		virtual void inline SetVec3(const std::string& name, glm::vec3 value) const override {
			glUniform3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
		}
		virtual void inline SetVec4(const std::string& name, float x, float y, float z, float w) const override {
			glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z, w);
		}
		virtual void inline SetVec4(const std::string& name, glm::vec4 value) const override {
			glUniform4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, glm::value_ptr(value));
		}
	private:
		std::unordered_map<GLenum, std::string> PreProcess(std::string& source);
		void CompileShader(const char* code, unsigned int& shader, GLenum type);
		void CheckError(unsigned int object, ErrorType type);
	private:
		unsigned int m_RendererID;
		std::string m_Path;
	};
}