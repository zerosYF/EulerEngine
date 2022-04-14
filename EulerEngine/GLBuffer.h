#pragma once
#include<glad/glad.h>
namespace EulerEngine {
	class VBO {
	private:
		unsigned int object;
	public:
		VBO() {
		}
		void BindVBO(float* vertices) {
			glGenBuffers(1, &object);
			glBindBuffer(GL_ARRAY_BUFFER, object);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		}
		void ReleaseVBO() {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	};
	class VAO {
	private:
		unsigned int object;
	public:
		VAO() {
		}
		void BindVAO() {
			if (object == 0) {
				glGenVertexArrays(1, &object);
				glBindVertexArray(object);
			}
		}
		void ReleaseVAO() {
			glBindVertexArray(0);
		}
	};
}