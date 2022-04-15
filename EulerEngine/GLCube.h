#pragma once
#include<glad/glad.h>
namespace EulerEngine {
	class CubeRender {
	private:
		unsigned int VAO;
		unsigned int VBO;
	public:
		float vertices[36 * 5] = {
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
	public:
		CubeRender() {
			this->Bind();
		}
		void Render(Shader &shader) {
			glBindVertexArray(VAO);
			glm::mat4 model = glm::mat4(1.0f);
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		void Bind() {
			glGenBuffers(1, &VBO);
			glGenVertexArrays(1, &VAO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		}
		void Release() {
			glDeleteVertexArrays(1, &VAO);
			glDeleteBuffers(1, &VBO);
		}
	};
}