#include"gkpch.h"
#include"EulerVertices.h"
namespace EulerEngine {
	float CubeVertices[CUBE_VERTEX_CNT*CUBE_DATA_SIZE] = {
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
	float SquareVertices[] = {
		//position			texCoord      normal
		0.0f,  0.5f,  0.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  1.0f, 0.0f,0.0f,0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f, 0.0f,0.0f,0.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  0.0f, 0.0f,0.0f,0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f, 0.0f,0.0f,0.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f,0.0f,0.0f
	};
}