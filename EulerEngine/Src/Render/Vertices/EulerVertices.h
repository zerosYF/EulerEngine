#pragma once
#include"gkpch.h"
#include"glm/glm.hpp"
#define CUBE_VERTEX_CNT 36
#define CUBE_DATA_SIZE 8
#define SQUARE_VERTEX_CNT 4
#define SQUARE_DATA_SIZE 5
namespace EulerEngine {
	extern float CubeVertices[CUBE_VERTEX_CNT*CUBE_DATA_SIZE];
	extern float SquareVertices[SQUARE_VERTEX_CNT*SQUARE_DATA_SIZE];
	extern float CubeVerticesWithoutNormal[CUBE_VERTEX_CNT*CUBE_DATA_SIZE];
	extern float SquareVerticesWithoutTexture[SQUARE_VERTEX_CNT*SQUARE_DATA_SIZE];
	extern struct CubeVertex{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		int GameObjectID = 0;
		//glm::vec3 Normal;
	};
	extern struct SquareVertex{
		glm::vec3 Position;
	};
}