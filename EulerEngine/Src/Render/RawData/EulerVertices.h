#pragma once
#include"glm/glm.hpp"
#define CUBE_VERTICE_CNT 36
#define CUBE_DATA_SIZE 8
#define QUAD_VERTICE_CNT 4
#define QUAD_DATA_SIZE 5
#define QUAD_INDEX_CNT 6
#define QUAD_VERTEX_CNT 4
namespace EulerEngine {
	extern float CubeVertices[CUBE_VERTICE_CNT * CUBE_DATA_SIZE];
	extern float QuadVertices[QUAD_VERTICE_CNT * QUAD_DATA_SIZE];
	extern unsigned int QuadIndices[QUAD_INDEX_CNT];
	class Generator {
	public:
		static unsigned int* GenerateCubeIndices(std::vector<unsigned int>& singleIndices, unsigned int count);
		static unsigned int* GenerateQuadIndices(std::vector<unsigned int>& singleIndices, unsigned int count);
	};
}  