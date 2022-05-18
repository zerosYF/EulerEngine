#pragma once
#define CUBE_VERTEX_CNT 36
#define CUBE_DATA_SIZE 8
#include"GLRenderObject.h"
#include<iostream>
using namespace std;
namespace EulerEngine {
	extern float vertices[CUBE_VERTEX_CNT*CUBE_DATA_SIZE] = {
		// Back face
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,0.0f,-1.0f,// Bottom-left
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,0.0f,-1.0f, // top-right
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,0.0f,-1.0f,// bottom-right         
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,0.0f,-1.0f,// top-right
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,0.0f,-1.0f,// bottom-left
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,0.0f,-1.0f,// top-left
		// Front face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,0.0f,0.0f,1.0f, // bottom-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,0.0f,1.0f,// bottom-right
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f,1.0f,// top-right
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,0.0f,1.0f, // top-right
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,0.0f,1.0f,// top-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,0.0f,1.0f,// bottom-left
		// Left face
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,0.0f,0.0f,// top-right
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,0.0f,0.0f,// top-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,0.0f,0.0f,// bottom-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,0.0f,0.0f,// bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,0.0f,0.0f,// bottom-right
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,0.0f,0.0f,// top-right
		// Right face
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,0.0f,0.0f, // top-left
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,0.0f,0.0f,// bottom-right
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,0.0f,0.0f,// top-right         
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,0.0f,0.0f,// bottom-right
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,1.0f,0.0f,0.0f, // top-left
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,0.0f,0.0f,// bottom-left     
		// Bottom face
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,-1.0f,0.0f,// top-right
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,-1.0f,0.0f, // top-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,-1.0f,0.0f,// bottom-left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,0.0f,-1.0f,0.0f, // bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,-1.0f,0.0f,// bottom-right
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,0.0f,-1.0f,0.0f, // top-right
		// Top face
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f,0.0f,// top-left
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,0.0f,1.0f,0.0f, // bottom-right
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,1.0f,0.0f,// top-right     
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f,0.0f,// bottom-right
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f,0.0f,// top-left
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,1.0f,0.0f // bottom-left
	};
	class Cube :public RenderObject{
	public:
		Cube(float* vertices) :RenderObject(vertices) {
			cout<<"生成立方体模板"<<endl;
		}
	};
	Cube* InitCube() {
		Cube *cube = new Cube(vertices);
		return cube;
	}
}