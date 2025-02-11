#pragma once
#include"gkpch.h"
#define CUBE_VERTEX_CNT 36
#define CUBE_DATA_SIZE 8
#define SQUARE_VERTEX_CNT 4
#define SQUARE_DATA_SIZE 5
namespace EulerEngine {
	extern float CubeVertices[CUBE_VERTEX_CNT*CUBE_DATA_SIZE];
	extern float SquareVertices[SQUARE_VERTEX_CNT*SQUARE_DATA_SIZE];
	extern float CubeVerticesWithoutNormal[CUBE_VERTEX_CNT*CUBE_DATA_SIZE];
	extern float SquareVerticesWithoutTexture[SQUARE_VERTEX_CNT*SQUARE_DATA_SIZE];
}