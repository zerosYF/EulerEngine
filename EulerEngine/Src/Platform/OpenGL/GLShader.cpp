#include"gkpch.h"
#include"GLShader.h"
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<iostream>
#include<fstream>
#include<filesystem>
namespace EulerEngine {
	static GLenum ShaderTypeFromString(std::string& type) {
		if (type == "vertex") return GL_VERTEX_SHADER;
		else if (type == "fragment") return GL_FRAGMENT_SHADER;
		std::cout << "which type of shader?" << std::endl;
		return 0;
	}
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {

		this->m_Name = name;
		unsigned int vertexShader;
		CompileShader(vertexSrc.c_str(), vertexShader, EULER_VERTEX);
		unsigned int fragmentShader;
		CompileShader(fragmentSrc.c_str(), fragmentShader, EULER_FRAGMENT);
		unsigned int program = glCreateProgram();
		m_RendererID = program;
		std::cout << "��Ⱦ��ID��" << program << std::endl;
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		CheckError(program, EULER_LINK_PROGRAM);
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	OpenGLShader::OpenGLShader(const std::string & path)
	{
		std::ifstream ShaderFile;

		ShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		try {
			ShaderFile.open(path, std::ios::in, std::ios::binary);
			std::stringstream ShaderStream;
			ShaderStream << ShaderFile.rdbuf();
			std::string shaderSource = ShaderStream.str();
			unsigned int vertexShader;
			unsigned int fragmentShader;
			auto shaders = PreProcess(shaderSource);
			for (auto& kv : shaders) {
				GLenum type = kv.first;
				if (type == GL_VERTEX_SHADER) {
					CompileShader(kv.second.c_str(), vertexShader, EULER_VERTEX);
				}
				else if (type == GL_FRAGMENT_SHADER) {
					CompileShader(kv.second.c_str(), fragmentShader, EULER_FRAGMENT);
				}
			}
			unsigned int program = glCreateProgram();
			m_RendererID = program;
			std::cout << "��Ⱦ��ID��" << program << std::endl;
			glAttachShader(program, vertexShader);
			glAttachShader(program, fragmentShader);

			glLinkProgram(program);
			CheckError(program, EULER_LINK_PROGRAM);
			glDetachShader(program, vertexShader);
			glDetachShader(program, fragmentShader);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			auto lastSlash = path.find_last_of("/\\");
			lastSlash = lastSlash == path.npos ? 0 : lastSlash + 1;
			auto lastDot = path.rfind('.');
			auto count = lastDot == path.npos ? path.size() - lastSlash : lastDot - lastSlash;
			this->m_Name = path.substr(lastSlash, count);
		}
		catch (std::ifstream::failure e) {
			std::cout << "Read File Failed" << std::endl;
		}
	}
	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererID);
	}
	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(std::string & source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			if (eol == std::string::npos) {
				std::cout << "error" << std::endl;
			}
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			if (type != "vertex" && type != "fragment") {
				std::cout << "error" << std::endl;
			}
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] 
				= source.substr(nextLinePos, pos - (nextLinePos == std::string::npos? source.size() - 1:nextLinePos));
		}
		return shaderSources;
	}
	void OpenGLShader::CompileShader(const char* Code, unsigned int& shader, CompileShaderType type) {
		if (type == EULER_VERTEX)
			shader = glCreateShader(GL_VERTEX_SHADER);
		else if (type == EULER_FRAGMENT)
			shader = glCreateShader(GL_FRAGMENT_SHADER);
		else
			shader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(shader, 1, &Code, NULL);
		glCompileShader(shader);
		CheckError(shader, type);
	}
	void OpenGLShader::CheckError(unsigned int object, unsigned int type) {
		int success;
		char infoLog[512];
		if (type != EULER_LINK_PROGRAM) {
			glGetShaderiv(object, GL_COMPILE_STATUS, &success);
			if (!success) {
				std::string t;
				if (type == EULER_VERTEX) t = "����shader";
				else if (type == EULER_FRAGMENT) t = "Ƭ��shader";
				else if (type == EULER_GEOMETRY) t = "����shader";

				glGetShaderInfoLog(object, 512, NULL, infoLog);
				std::cout << t << "����ʧ��\n" << "log: " << infoLog << std::endl;
			}
		}
		else {
			glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(object, 512, NULL, infoLog);
				std::cout << "����ʧ��\n" << "log: " << infoLog << std::endl;
				glDeleteProgram(object);
			}
		}
	}
	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);
	}
	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}
}