#include"gkpch.h"
#include"EulerVertices.h"
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	extern float CubeVertices[CUBE_VERTICE_CNT * CUBE_DATA_SIZE] = {
		//Pos                 TexCoord    Normal
		// Back face
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,0.0f,-1.0f,// Bottom-left
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,0.0f,-1.0f, // top-right
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,0.0f,-1.0f,// bottom-right         
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,0.0f,-1.0f,// top-right
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,0.0f,-1.0f,// bottom-left
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,0.0f,-1.0f,// top-left
		// Front face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,0.0f,1.0f, // bottom-left
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,0.0f,1.0f,// bottom-right
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f,1.0f,// top-right
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f,1.0f, // top-right
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,0.0f,1.0f,// top-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,0.0f,1.0f,// bottom-left
		// Left face
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,0.0f,0.0f,// top-right
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,0.0f,0.0f,// top-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,0.0f,0.0f,// bottom-left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,0.0f,0.0f,// bottom-left
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,0.0f,0.0f,// bottom-right
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,0.0f,0.0f,// top-right
		// Right face
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,0.0f,0.0f, // top-left
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,0.0f,0.0f,// bottom-right
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,0.0f,0.0f,// top-right         
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,0.0f,0.0f,// bottom-right
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,0.0f,0.0f, // top-left
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,0.0f,0.0f,// bottom-left     
		 // Bottom face
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,-1.0f,0.0f,// top-right
		  0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,-1.0f,0.0f, // top-left
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,-1.0f,0.0f,// bottom-left
		  0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,-1.0f,0.0f, // bottom-left
		 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,-1.0f,0.0f,// bottom-right
		 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,-1.0f,0.0f, // top-right
		 // Top face
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f,0.0f,// top-left
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f,0.0f, // bottom-right
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,1.0f,0.0f,// top-right     
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f,0.0f,// bottom-right
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f,0.0f,// top-left
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,1.0f,0.0f // bottom-left
	};
	extern float QuadVertices[QUAD_VERTICE_CNT * QUAD_DATA_SIZE] = {
		//position			texCoord      
		-0.5f, -0.5f,  0.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	};
	extern unsigned int QuadIndices[QUAD_INDEX_CNT] = { 0, 1, 2, 2, 3, 0 };
	unsigned int* Generator::GenerateCubeIndices(std::vector<unsigned int>& singleIndices, unsigned int count)
	{
		return nullptr;
	}
	unsigned int* Generator::GenerateQuadIndices(std::vector<unsigned int>& singleIndices, unsigned int count)
	{
		unsigned int offset = 0;
		unsigned int* QuadIndices = new unsigned int[count];
		for (unsigned int i = 0; i < count; i += QUAD_INDEX_CNT) {
			for (unsigned int j = 0; j < QUAD_INDEX_CNT; j++) {
				QuadIndices[i + j] = offset + singleIndices[j];
			}
			offset += QUAD_VERTEX_CNT;
		}
		//KINK_CORE_INFO("{0} Quad Indices Generated.", count);
		return QuadIndices;
	}
}