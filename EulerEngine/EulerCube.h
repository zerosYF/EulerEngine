#pragma once
#include<glad/glad.h>
namespace EulerEngine {
	float CubeVertices[36 * 5] = {
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // Bottom-left
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f,  // top-right
			0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-right         
			0.5f, 0.5f, -0.5f, 0.0f, 0.0f,  // top-right
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,   // bottom-left
			-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, // top-left
			// Front face
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // bottom-left
			0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // bottom-right
			0.5f, 0.5f, 0.5f, 0.0f, 0.0f,   // top-right
			0.5f, 0.5f, 0.5f, 0.0f, 0.0f,  // top-right
			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,   // top-left
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // bottom-left
			// Left face
			-0.5f, 0.5f, 0.5f, -1.0f, 0.0f,  // top-right
			-0.5f, 0.5f, -0.5f, -1.0f, 0.0f,  // top-left
			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f,   // bottom-left
			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, // bottom-left
			-0.5f, -0.5f, 0.5f, -1.0f, 0.0f,   // bottom-right
			-0.5f, 0.5f, 0.5f, -1.0f, 0.0f,  // top-right
			// Right face
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,  // top-left
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // bottom-right
			0.5f, 0.5f, -0.5f, 1.0f, 0.0f,  // top-right         
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f,   // bottom-right
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // top-left
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  // bottom-left     
			// Bottom face
			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  // top-right
			0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  // top-left
			0.5f, -0.5f, 0.5f, 0.0f, -1.0f, // bottom-left
			0.5f, -0.5f, 0.5f, 0.0f, -1.0f,  // bottom-left
			-0.5f, -0.5f, 0.5f, 0.0f, -1.0f,  // bottom-right
			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, // top-right
			// Top face
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
			0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // bottom-right
			0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  // top-right     
			0.5f, 0.5f, 0.5f, 0.0f, 1.0f, // bottom-right
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // bottom-left     
	};
	class Cube {
	private:
		unsigned int VAO;
	public:
		Cube() {
		}
		void VAOConfig() {
		}
		void BindVAO() {
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		}
	};
}