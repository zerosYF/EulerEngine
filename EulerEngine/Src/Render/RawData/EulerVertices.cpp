#include"gkpch.h"
#include"EulerVertices.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	extern float CubeVertices[CUBE_VERTEX_CNT * CUBE_DATA_SIZE] = {
		//Pos                 TexCoord    Normal
		// Back face
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	0.0f,0.0f,-1.0f,// Bottom-left
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.0f,0.0f,-1.0f, // top-right
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,	0.0f,0.0f,-1.0f,// bottom-right         
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.0f,0.0f,-1.0f,// top-right
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	0.0f,0.0f,-1.0f,// bottom-left
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	0.0f,0.0f,-1.0f,// top-left
		// Front face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.0f,0.0f,1.0f, // bottom-left
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	0.0f,0.0f,1.0f,// bottom-right
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	0.0f,0.0f,1.0f,// top-right
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	0.0f,0.0f,1.0f, // top-right
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,	0.0f,0.0f,1.0f,// top-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.0f,0.0f,1.0f,// bottom-left
		// Left face
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	-1.0f,0.0f,0.0f,// top-right
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	-1.0f,0.0f,0.0f,// top-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	-1.0f,0.0f,0.0f,// bottom-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	-1.0f,0.0f,0.0f,// bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	-1.0f,0.0f,0.0f,// bottom-right
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	-1.0f,0.0f,0.0f,// top-right
		// Right face
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,0.0f,0.0f, // top-left
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,0.0f,0.0f,// bottom-right
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   1.0f,0.0f,0.0f,// top-right         
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,0.0f,0.0f,// bottom-right
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,0.0f,0.0f, // top-left
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f,0.0f,0.0f,// bottom-left     
		 // Bottom face
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f,-1.0f,0.0f,// top-right
		  0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f,-1.0f,0.0f, // top-left
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f,-1.0f,0.0f,// bottom-left
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f,-1.0f,0.0f, // bottom-left
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,-1.0f,0.0f,// bottom-right
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f,-1.0f,0.0f, // top-right
		 // Top face
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,1.0f,0.0f,// top-left
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,1.0f,0.0f, // bottom-right
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,1.0f,0.0f,// top-right     
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,1.0f,0.0f,// bottom-right
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,1.0f,0.0f,// top-left
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f,1.0f,0.0f // bottom-left
	};
	extern float SpriteVertices[SPRITE_VERTEX_CNT * SPRITE_DATA_SIZE] = {
		//position			  texCoord      
		-0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	};
	extern float PlaneVertices[PLANE_VERTEX_CNT * PLANE_DATA_SIZE] = {
		//position			  texCoord		normal
		-0.5f,  0.0f, -0.5f,  0.0f, 0.0f,	0.0f,  1.0f, 0.0f,
		 0.5f,  0.0f, -0.5f,  1.0f, 0.0f,	0.0f,  1.0f, 0.0f,
		 0.5f,  0.0f,  0.5f,  1.0f, 1.0f,	0.0f,  1.0f, 0.0f,
		-0.5f,  0.0f,  0.5f,  0.0f, 1.0f,	0.0f,  1.0f, 0.0f,

		-0.5f,  0.0f, -0.5f,  0.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		 0.5f,  0.0f, -0.5f,  1.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		 0.5f,  0.0f,  0.5f,  1.0f, 1.0f,	0.0f, -1.0f, 0.0f,
		-0.5f,  0.0f,  0.5f,  0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
	};
	extern unsigned int SpriteIndices[SPRITE_INDEX_CNT] = { 0, 1, 2, 2, 3, 0 };
	extern unsigned int PlaneIndices[PLANE_INDEX_CNT] = { 0, 1, 2, 0, 2, 3, 4, 6, 5, 4, 7, 6 };
	unsigned int* Generator::GenerateIndices(std::vector<unsigned int>& singleIndices, unsigned int totalCount, const unsigned int vertexCnt)
	{
		unsigned int* Indices = new unsigned int[totalCount];
		const unsigned int step = singleIndices.size();
		if (step == 0) {
			return Indices;
		}
		KINK_CORE_ASSERT(totalCount % step == 0, "Invalid count of indices for Plane Indices Generation.");
		unsigned int offset = 0;
		for (unsigned int i = 0; i < totalCount; i += step) {
			unsigned int j = 0;
			for (auto x: singleIndices) {
				Indices[i + j++] = offset + x;
			}
			offset += vertexCnt;
		}
		return Indices;
	}
	std::vector<float>& Generator::GenerateSphereVertices(int slices, int stacks, float radius)
	{
		//Todo: Generate Sphere Vertices
		return std::vector<float>();
	}
	std::vector<unsigned int>& Generator::GenerateSphereIndices(int slices, int stacks)
	{
		//Todo: Generate Sphere Indices
		return std::vector<unsigned int>();
	}
}