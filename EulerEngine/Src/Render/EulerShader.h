#pragma once
#include<string>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glad/glad.h>
namespace EulerEngine {
	class EulerShader {
	public:
		virtual ~EulerShader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static EulerShader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	private:
		unsigned int m_RendererID;

	};
}