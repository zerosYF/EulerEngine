#pragma once
#include<string>
#include"GutKink/Core.h"
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"glad/glad.h"
namespace EulerEngine {
	class EulerShader {
	public:
		virtual ~EulerShader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual std::string GetPath() const = 0;

		static Ref<EulerShader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
		//uniform;
		virtual void inline SetBool(const std::string& name, bool value) const = 0;
		virtual void inline SetInt(const std::string& name, int value) const = 0;
		virtual void inline SetIntArray(const std::string& name, int* values, unsigned int count) const = 0;
		virtual void inline SetFloat(const std::string& name, float value) const = 0;
		virtual void inline SetMat3(const std::string& name, glm::mat3 value) const = 0;
		virtual void inline SetMat4(const std::string& name, glm::mat4 value) const = 0;
		virtual void inline SetVec2(const std::string& name, float x, float y) const = 0;
		virtual void inline SetVec2(const std::string& name, glm::vec2 value) const = 0;
		virtual void inline SetVec3(const std::string& name, float x, float y, float z) const = 0;
		virtual void inline SetVec3(const std::string& name, glm::vec3 value) const = 0;
		virtual void inline SetVec4(const std::string& name, float x, float y, float z, float w) const = 0;
		virtual void inline SetVec4(const std::string& name, glm::vec4 value) const = 0;
	private:
		static Ref<EulerShader> Create(const std::string& path);
		friend class ResourceLibrary;
	};
}