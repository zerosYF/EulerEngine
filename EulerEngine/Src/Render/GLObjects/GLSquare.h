#pragma once
#include"GLRenderObject.h"
#include<iostream>
namespace EulerEngine {
	class Square :public RenderObject{
	public:
		Square(float* vertices) :RenderObject(vertices) {
			std::cout << "����������ģ��" << std::endl;
		}
	};
}