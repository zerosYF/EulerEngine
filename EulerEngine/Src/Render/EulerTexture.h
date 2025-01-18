#pragma once
#include<iostream>
#include"GutKink/Core.h"
#ifndef  TEXTURE_H
#define TEXTURE_H
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
		virtual void Bind(unsigned int slot=0) const = 0;
	};
	class Texture2D :public Texture {
	public:
		static Texture2D* Create(const std::string& path);
	};
	
}
#endif
