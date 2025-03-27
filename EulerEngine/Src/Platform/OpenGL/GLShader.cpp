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
		else if (type == "geometry") return GL_GEOMETRY_SHADER;
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
		CompileShader(vertexSrc.c_str(), vertexShader, GL_VERTEX_SHADER);
		unsigned int fragmentShader;
		CompileShader(fragmentSrc.c_str(), fragmentShader, GL_FRAGMENT_SHADER);
		unsigned int program = glCreateProgram();
		m_RendererID = program;
		std::cout << "GL_program_ID:" << program << std::endl;
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		CheckError(program, ErrorType::LINK);
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	OpenGLShader::OpenGLShader(const std::string & path):m_Path(path)
	{
		//CreateCacheDirectoryIfNeeded();
		std::string shaderSource = FileSystem::ReadFileText(path);
		std::unordered_map<GLenum, unsigned int> shader_objs;
		shader_objs[GL_VERTEX_SHADER] = 0;
		shader_objs[GL_FRAGMENT_SHADER] = 0;
		auto shaders = PreProcess(shaderSource);
		std::string fileName = FileSystem::GetFileName(path);
		KINK_CORE_INFO("SHADER NAME: {0}", fileName);

		for (auto& kv : shaders) {
			CompileShader(kv.second.c_str(), shader_objs[kv.first], kv.first);
		}
		unsigned int program = glCreateProgram();
		m_RendererID = program;
		KINK_CORE_INFO("GL_PROGRAM_ID: {0}", m_RendererID);
		for (auto& kv : shader_objs) {
			glAttachShader(program, kv.second);
		}
		glLinkProgram(program);
		CheckError(program, ErrorType::LINK);
		for (auto& kv : shader_objs) {
			glDetachShader(program, kv.second);
			glDeleteShader(kv.second);
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
	void OpenGLShader::CompileShader(const char* code, unsigned int& shader, GLenum type) {
		shader = glCreateShader(type);
		glShaderSource(shader, 1, &code, NULL);
		glCompileShader(shader);
		KINK_CORE_INFO("COMPILE SHADER...{0}", shader);
		CheckError(shader, ErrorType::COMPILE);
	}
	void OpenGLShader::CheckError(unsigned int object, ErrorType type) {
		int success;
		char infoLog[512];
		if (type != ErrorType::LINK) {
			glGetShaderiv(object, GL_COMPILE_STATUS, &success);
			if (!success) {
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