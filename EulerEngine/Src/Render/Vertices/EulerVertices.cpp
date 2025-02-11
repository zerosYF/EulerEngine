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
	float CubeVerticesWithoutNormal[CUBE_VERTEX_CNT*CUBE_DATA_SIZE] = {
		//Pos                 TexCoord    
		// Back face
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,          
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 
		// Front face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
		// Left face
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
		// Right face
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,      
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,    
		// Bottom face
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
		// Top face
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 
	};
	float SquareVertices[SQUARE_VERTEX_CNT * SQUARE_DATA_SIZE] = {
		//position			texCoord      
		0.0f,  0.5f,  0.0f,  0.0f,  0.0f, 
		0.0f, -0.5f,  0.0f,  0.0f,  1.0f, 
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f, 

		0.0f,  0.5f,  0.0f,  0.0f,  0.0f, 
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f, 
		1.0f,  0.5f,  0.0f,  1.0f,  0.0f, 
	};
	float SquareVerticesWithoutTexture[SQUARE_VERTEX_CNT * SQUARE_DATA_SIZE] = {
		//position			 
		0.0f,  0.5f,  0.0f, 
		0.0f, -0.5f,  0.0f, 
		1.0f, -0.5f,  0.0f, 

		0.0f,  0.5f,  0.0f, 
		1.0f, -0.5f,  0.0f, 
		1.0f,  0.5f,  0.0f, 
	};
}