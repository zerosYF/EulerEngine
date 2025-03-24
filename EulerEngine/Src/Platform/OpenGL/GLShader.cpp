#include"gkpch.h"
#include"GLShader.h"
#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<filesystem>
#include"Core/Logs/EulerLog.h"
#include"Core/IO/FileSystem.h"
namespace EulerEngine {
	static GLenum ShaderTypeFromString(std::string& type) {
		if (type == "vertex") return GL_VERTEX_SHADER;
		else if (type == "fragment") return GL_FRAGMENT_SHADER;
		std::cout << "which type of shader?" << std::endl;
		return 0;
	}
	static std::string GetCacheDirectory() {
		return "assets/cache/shaders/opengl";
	}
	static void CreateCacheDirectoryIfNeeded() {
		std::string cacheDir = GetCacheDirectory();
		if (!std::filesystem::exists(cacheDir)) {
			std::filesystem::create_directory(cacheDir);
		}
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc) {

		unsigned int vertexShader;
		CompileShader(vertexSrc.c_str(), vertexShader, EULER_VERTEX);
		unsigned int fragmentShader;
		CompileShader(fragmentSrc.c_str(), fragmentShader, EULER_FRAGMENT);
		unsigned int program = glCreateProgram();
		m_RendererID = program;
		std::cout << "GL_program_ID:" << program << std::endl;
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		CheckError(program, EULER_LINK_PROGRAM);
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	OpenGLShader::OpenGLShader(const std::string & path):m_Path(path)
	{
		//CreateCacheDirectoryIfNeeded();
		std::string shaderSource = FileSystem::ReadFileText(path);
		unsigned int vertexShader = 0;
		unsigned int fragmentShader = 0;
		auto shaders = PreProcess(shaderSource);
		std::string fileName = FileSystem::GetFileName(path);
		KINK_CORE_INFO("SHADER NAME: {0}", fileName);

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
		KINK_CORE_INFO("GL_PROGRAM_ID: {0}", m_RendererID);
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
		KINK_CORE_INFO("COMPILE SHADER...{0}", shader);
		CheckError(shader, type);
	}
	void OpenGLShader::CheckError(unsigned int object, unsigned int type) {
		int success;
		char infoLog[512];
		if (type != EULER_LINK_PROGRAM) {
			glGetShaderiv(object, GL_COMPILE_STATUS, &success);
			if (!success) {
				std::string t;
				if (type == EULER_VERTEX) t = "vertex shader";
				else if (type == EULER_FRAGMENT) t = "fragment shader";
				else if (type == EULER_GEOMETRY) t = "geometry shader";

				glGetShaderInfoLog(object, 512, NULL, infoLog);
				KINK_CORE_ERROR("INFO: {0}", infoLog);
			}
		}
		else {
			glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(object, 512, NULL, infoLog);
				KINK_CORE_ERROR("INFO: {0}", infoLog);
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
	std::string OpenGLShader::GetPath() const
	{
		return m_Path;
	}
}