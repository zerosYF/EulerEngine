#pragma once
#include<string>
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
	private:
		void CompileShader(const char* Code, unsigned int& shader, CompileShaderType type);
		void CheckError(unsigned int object, unsigned int type);
	private:
		unsigned int m_RendererID;

	}
}