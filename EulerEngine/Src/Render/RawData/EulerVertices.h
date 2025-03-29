#pragma once
#include"glm/glm.hpp"
#include<vector>
#define CUBE_DATA_SIZE 8
#define CUBE_INDEX_CNT 36
#define CUBE_VERTEX_CNT 36

#define PLANE_DATA_SIZE 8
#define PLANE_INDEX_CNT 12
#define PLANE_VERTEX_CNT 8

#define SPHERE_DATA_SIZE 100
#define SPHERE_INDEX_CNT 360
#define SPHERE_VERTEX_CNT 100

#define SPRITE_DATA_SIZE 5
#define SPRITE_INDEX_CNT 6
#define SPRITE_VERTEX_CNT 4
namespace EulerEngine {
	extern float CubeVertices[CUBE_VERTEX_CNT * CUBE_DATA_SIZE];
	extern float SpriteVertices[SPRITE_VERTEX_CNT * SPRITE_DATA_SIZE];
	extern float PlaneVertices[PLANE_VERTEX_CNT * PLANE_DATA_SIZE];
	extern unsigned int SpriteIndices[SPRITE_INDEX_CNT];
	extern unsigned int PlaneIndices[PLANE_INDEX_CNT];
	class Generator {
	public:
		static unsigned int* GenerateIndices(std::vector<unsigned int>& singleIndices, unsigned int totalCount, const unsigned int vertexCnt);

		static std::vector<float>& GenerateSphereVertices(int slices, int stacks, float radius);
		static std::vector<unsigned int>& GenerateSphereIndices(int slices, int stacks);
	};
}  