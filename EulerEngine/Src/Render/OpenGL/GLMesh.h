#pragma once
#include"../../Math/EulerMath.h"
#include <string>
#include <vector>
#include "GLShader.h"

//struct Vertex{
//	glm::vec3 Position;
//	glm::vec2 TexCoords;
//	glm::vec3 Normal;
//};
//struct Triangle {
//	Vertex vertexs[3];
//};
//class Mesh {
//public:
//	std::vector<Vertex> vertices;
//	std::vector<unsigned int> indices;
//	Mesh() {
//	}
//	void setupVertex(std::vector<Vertex> v, std::vector<unsigned int> i) {
//		vertices = v;
//		indices = i;
//		this->setupMesh();
//	}
//	void Draw(Shader shader) {
//		glBindVertexArray(VAO);
//		if(indices.size()!=0)
//			glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
//		else {
//			glDrawArrays(GL_TRIANGLES,0,vertices.size());
//		}
//		glBindVertexArray(0);
//	}
//	unsigned int getVAO() {
//		return this->VAO;
//	}
//private:
//	unsigned int VAO, VBO, EBO;
//	void setupMesh() {
//		glGenVertexArrays(1,&VAO);
//		glGenBuffers(1,&VBO);
//		glGenBuffers(1,&EBO);
//
//		glBindVertexArray(VAO);
//		glBindBuffer(GL_ARRAY_BUFFER,VBO);
//		glBufferData(GL_ARRAY_BUFFER,
//			vertices.size()*sizeof(Vertex),&vertices[0],GL_STATIC_DRAW);
//		if (indices.size() != 0) {
//			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//			glBufferData(GL_ELEMENT_ARRAY_BUFFER,
//				indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
//		}
//
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,
//			sizeof(Vertex),(void*)offsetof(Vertex, Position));
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,
//			sizeof(Vertex),(void*)offsetof(Vertex,TexCoords));
//		glEnableVertexAttribArray(2);
//		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,
//			sizeof(Vertex),(void*)offsetof(Vertex,Normal));
//		
//		glBindVertexArray(0);
//	}
//};
