#pragma once
#include"gkpch.h"
#include"glm/glm.hpp"
#define CUBE_VERTICE_CNT 36
#define CUBE_DATA_SIZE 8
#define QUAD_VERTICE_CNT 4
#define QUAD_DATA_SIZE 5
namespace EulerEngine {
	extern float CubeVertices[CUBE_VERTICE_CNT *CUBE_DATA_SIZE];
	extern float QuadVertices[QUAD_VERTICE_CNT * QUAD_DATA_SIZE];
	extern float CubeVerticesWithoutNormal[CUBE_VERTICE_CNT *CUBE_DATA_SIZE];
	extern float QuadVerticesWithoutTexture[QUAD_VERTICE_CNT * QUAD_DATA_SIZE];
	extern struct CubeVertex{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		int GameObjectID = 0;
	};
	extern struct QuadVertex{
		glm::vec3 Position;
		glm::vec2 TexCoord;
		int GameObjectID = 0;
	};
	extern struct CircleVertex {
		glm::vec3 Position;
		glm::vec3 LocalPosition;
		glm::vec4 Color;
		float Thickness;
		float Fade;
		int GameObjectID = 0;
	};
	extern struct LineVertex {
		glm::vec3 Position;
		glm::vec4 Color;
		int GameObjectID = 0;
	};
}