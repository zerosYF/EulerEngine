#pragma once
#include"GLRenderObject.h"
#include<iostream>
using namespace std;
namespace EulerEngine {
	extern float SquareVertices[] = {
		//position			texCoord      normal
		0.0f,  0.5f,  0.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f,0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f, 0.0f,0.0f,0.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f, 0.0f,0.0f,0.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f,0.0f,0.0f
	};
	class Square :public RenderObject{
	public:
		Square(float* vertices) :RenderObject(vertices) {
			cout << "生成正方形模板" << endl;
		}
	};
	Square* InitSquare() {
		Square *square = new Square(SquareVertices);
		return square;
	}
}