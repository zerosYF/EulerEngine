#include"gkpch.h"
#include"GLShader.h"
#include<GLFW/glfw3.h>
#include<glad/glad.h>
namespace EulerEngine {
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc) {

		unsigned int vertexShader;
		CompileShader(vertexSrc.c_str(), vertexShader, EULER_VERTEX);
		unsigned int fragmentShader;
		CompileShader(fragmentSrc.c_str(), fragmentShader, EULER_FRAGMENT);
		unsigned int program = glCreateProgram();
		m_RendererID = program;
		std::cout << "äÖÈ¾Æ÷ID£º" << program << std::endl;
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		CheckError(program, EULER_LINK_PROGRAM);
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererID);
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
				if (type == EULER_VERTEX) t = "¶¥µãshader";
				else if (type == EULER_FRAGMENT) t = "Æ¬¶Îshader";
				else if (type == EULER_GEOMETRY) t = "¼¸ºÎshader";

				glGetShaderInfoLog(object, 512, NULL, infoLog);
				std::cout << t << "±àÒëÊ§°Ü\n" << "log: " << infoLog << std::endl;
			}
		}
		else {
			glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(object, 512, NULL, infoLog);
				std::cout << "Á´½ÓÊ§°Ü\n" << "log: " << infoLog << std::endl;
				glDeleteProgram(object);
			}
		}
	}
	void EulerShader::Bind() const {
		glUseProgram(m_RendererID);
	}
	void EulerShader::Unbind() const {
		glUseProgram(0);
	}
}