#pragma once
#include<iostream>
#include"GutKink/Core.h"
#include<glfw/glfw3.h>
#include<glad/glad.h>
#include<string>
namespace EulerEngine {
	enum TextureType {
		DIFFUSE,
		SPECULAR,
	};
	class Texture {
	public:
		virtual ~Texture() = default;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual void SetData(void* data, unsigned int size) = 0;
		virtual void Bind(unsigned int slot=0) const = 0;
		virtual bool operator==(const Texture& another) const = 0;
		virtual std::string GetPath() const = 0;
		virtual unsigned int GetRendererID() const = 0;
	};
	class Texture2D :public Texture {
	public:
		static Ref<Texture2D> Create(unsigned int width, unsigned int height);
	private:
		static Ref<Texture2D> Create(const std::string& path);
		friend class ResourceLibrary;
	};
	
}
