#pragma once
namespace EulerEngine {
	//float lerp(float a, float b, float f) {
	//	return a + f * (b - a);
	//}
	////ssao半球样本随机；
	//vector<glm::vec3> SampleKernel() {
	//	//左闭右开均匀浮点分布；
	//	uniform_real_distribution<float> randomFloat(0.0, 1.0);
	//	default_random_engine random_generator;
	//	vector<glm::vec3> ssaoKernel;
	//	for (int i = 0; i < 64; i++) {
	//		float x = randomFloat(random_generator)*2.0 - 1.0;
	//		float y = randomFloat(random_generator)*2.0 - 1.0;
	//		float z = randomFloat(random_generator);
	//		glm::vec3 sample(x, y, z);
	//		sample = glm::normalize(sample);
	//		sample *= randomFloat(random_generator);
	//		float scale = float(i) / 64.0;
	//		scale = lerp(0.1f, 1.0f, scale*scale);
	//		sample *= scale;
	//		ssaoKernel.push_back(sample);
	//	}
	//	return ssaoKernel;
	//}
	////噪声；
	//vector<glm::vec3> Noise() {
	//	vector<glm::vec3> ssaoNoise;
	//	uniform_real_distribution<float> randomFloat(0.0, 1.0);
	//	default_random_engine random_generator;
	//	for (int i = 0; i < 16; i++) {
	//		int x = randomFloat(random_generator)*2.0 - 1.0;
	//		int y = randomFloat(random_generator)*2.0 - 1.0;
	//		glm::vec3 noise(x, y, 0.0);
	//		ssaoNoise.push_back(noise);
	//	}
	//	return ssaoNoise;
	//}

	//unsigned int wood;
	//unsigned int container;
	//Model nano;

	//unsigned int cubeVAO = 0;
	//unsigned int cubeVBO = 0;
	//float CubeVertices[] = {
	//			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
	//			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
	//			0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
	//			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  // top-right
	//			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // bottom-left
	//			-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,// top-left
	//			// Front face
	//			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
	//			0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
	//			0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // top-right
	//			0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
	//			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
	//			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom-left
	//			// Left face
	//			-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
	//			-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
	//			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-left
	//			-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
	//			-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
	//			-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
	//			// Right face
	//			0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
	//			0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
	//			0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right         
	//			0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-right
	//			0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // top-left
	//			0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left     
	//			// Bottom face
	//			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
	//			0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
	//			0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,// bottom-left
	//			0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
	//			-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
	//			-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
	//			// Top face
	//			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
	//			0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
	//			0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right     
	//			0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
	//			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
	//			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f // bottom-left     
	//};
	//void renderCube() {
	//	if (cubeVAO == 0) {
	//		glGenVertexArrays(1, &cubeVAO);
	//		glGenBuffers(1, &cubeVBO);
	//		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	//		glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);
	//		glBindVertexArray(cubeVAO);
	//		glEnableVertexAttribArray(0);
	//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	//		glEnableVertexAttribArray(1);
	//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//		glEnableVertexAttribArray(2);
	//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//		glBindBuffer(GL_ARRAY_BUFFER, 0);
	//		glBindVertexArray(0);
	//	}
	//	glBindVertexArray(cubeVAO);
	//	glDrawArrays(GL_TRIANGLES, 0, 36);
	//	glBindVertexArray(0);
	//}

	//unsigned int sphereVAO = 0;
	//unsigned int indexCount;
	//void renderSphere() {
	//	if (sphereVAO == 0) {
	//		glGenVertexArrays(1, &sphereVAO);
	//		unsigned int vbo, ebo;
	//		glGenBuffers(1, &vbo);
	//		glGenBuffers(1, &ebo);
	//		vector<glm::vec3> Positions;
	//		vector<glm::vec2> uv;
	//		//v:半径线与z轴正向的夹角；u:半径线在xy平面投影与x轴正向夹角；
	//		vector<glm::vec3> normals;
	//		vector<unsigned int> indices;
	//		const unsigned int X_SEGMENTS = 64;
	//		const unsigned int Y_SEGMENTS = 64;
	//		const float PI = 3.14159265359;
	//		for (int y = 0; y <= Y_SEGMENTS; y++) {
	//			for (int x = 0; x <= X_SEGMENTS; x++) {
	//				float xSegment = (float)x / (float)X_SEGMENTS;
	//				float ySegment = (float)y / (float)Y_SEGMENTS;
	//				float v = ySegment * PI, u = xSegment * 2.0*PI;
	//				float xPos = cos(u)*sin(v);
	//				float yPos = cos(v);
	//				float zPos = sin(u)*sin(v);
	//				Positions.push_back(glm::vec3(xPos, yPos, zPos));
	//				uv.push_back(glm::vec2(xSegment, ySegment));
	//				normals.push_back(glm::vec3(xPos, yPos, zPos));
	//			}
	//		}
	//		bool oddRow = false;
	//		//奇偶交替；
	//		for (int y = 0; y < Y_SEGMENTS; y++) {
	//			if (!oddRow) {
	//				//even:0,2,4,...;
	//				for (int x = 0; x <= X_SEGMENTS; x++) {
	//					indices.push_back(y*(X_SEGMENTS + 1) + x);
	//					indices.push_back((y + 1)*(X_SEGMENTS + 1) + x);
	//				}
	//			}
	//			else {
	//				//odd:1,3,5,...;
	//				for (int x = X_SEGMENTS; x >= 0; x--) {
	//					indices.push_back((y + 1)*(X_SEGMENTS + 1) + x);
	//					indices.push_back(y*(X_SEGMENTS + 1) + x);
	//				}
	//			}
	//			oddRow = !oddRow;
	//		}
	//		indexCount = indices.size();
	//		vector<float> data;
	//		for (int i = 0; i < Positions.size(); i++) {
	//			data.push_back(Positions[i].x);
	//			data.push_back(Positions[i].y);
	//			data.push_back(Positions[i].z);
	//			if (uv.size() > 0) {
	//				data.push_back(uv[i].x);
	//				data.push_back(uv[i].y);
	//			}
	//			if (normals.size() > 0) {
	//				data.push_back(normals[i].x);
	//				data.push_back(normals[i].y);
	//				data.push_back(normals[i].z);
	//			}
	//		}
	//		glBindVertexArray(sphereVAO);
	//		glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	//		float stride = (3 + 2 + 3) * sizeof(float);
	//		glEnableVertexAttribArray(0);
	//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	//		glEnableVertexAttribArray(1);
	//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	//		glEnableVertexAttribArray(2);
	//		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
	//	}
	//	glBindVertexArray(sphereVAO);
	//	glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
	//}

	//unsigned int quadVAO = 0;
	//unsigned int quadVBO;
	//float quadVertices[] = {
	//	// positions        // texture Coords
	//	-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
	//	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	//	 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
	//	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	//};
	//void renderQuad() {
	//	if (quadVAO == 0) {
	//		glGenVertexArrays(1, &quadVAO);
	//		glGenBuffers(1, &quadVBO);
	//		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	//		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	//		glBindVertexArray(quadVAO);
	//		glEnableVertexAttribArray(0);
	//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	//		glEnableVertexAttribArray(1);
	//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//		glBindVertexArray(0);
	//	}
	//	glBindVertexArray(quadVAO);
	//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//	glBindVertexArray(0);
	//}

	//void calculatePos(glm::vec3 &tangent, glm::vec3 &bitangent,
	//	glm::vec3 edge1, glm::vec3 edge2, glm::vec2 dUV1, glm::vec2 dUV2) {
	//	float  f = 1.0f / (dUV2.y*dUV1.x - dUV1.y*dUV2.x);
	//	tangent.x = f * (dUV2.y*edge1.x - dUV1.y - edge2.x);
	//	tangent.y = f * (dUV2.y*edge1.y - dUV1.y - edge2.y);
	//	tangent.z = f * (dUV2.y*edge1.z - dUV1.y - edge2.z);
	//	tangent = glm::normalize(tangent);
	//	bitangent.x = f * (-dUV2.x*edge1.x + dUV1.x*edge2.x);
	//	bitangent.y = f * (-dUV2.x*edge1.y + dUV1.x*edge2.y);
	//	bitangent.z = f * (-dUV2.x*edge1.z + dUV1.x*edge2.z);
	//	bitangent = glm::normalize(bitangent);
	//}
	//unsigned int wallVAO = 0;
	//unsigned int wallVBO = 0;
	//void renderWall() {
	//	if (wallVAO == 0) {
	//		// positions
	//		glm::vec3 pos1(-1.0, 1.0, 0.0);
	//		glm::vec3 pos2(-1.0, -1.0, 0.0);
	//		glm::vec3 pos3(1.0, -1.0, 0.0);
	//		glm::vec3 pos4(1.0, 1.0, 0.0);
	//		// texture coordinates
	//		glm::vec2 uv1(0.0, 1.0);
	//		glm::vec2 uv2(0.0, 0.0);
	//		glm::vec2 uv3(1.0, 0.0);
	//		glm::vec2 uv4(1.0, 1.0);
	//		// normal vector
	//		glm::vec3 nm(0.0, 0.0, 1.0);

	//		glm::vec3 tangent1, bitangent1;
	//		glm::vec3 tangent2, bitangent2;

	//		glm::vec3 edge1 = pos2 - pos1;
	//		glm::vec3 edge2 = pos3 - pos1;

	//		glm::vec2 dUV1 = uv2 - uv1;
	//		glm::vec2 dUV2 = uv3 - uv1;
	//		calculatePos(tangent1, bitangent1, edge1, edge2, dUV1, dUV2);

	//		edge1 = pos3 - pos1;
	//		edge2 = pos4 - pos1;
	//		dUV1 = uv3 - uv1;
	//		dUV2 = uv4 - uv1;
	//		calculatePos(tangent2, bitangent2, edge1, edge2, dUV1, dUV2);
	//		float wallVertice[] = {
	//			// Positions            // normal         // TexCoords  // Tangent                          // Bitangent
	//			pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
	//			pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
	//			pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

	//			pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
	//			pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
	//			pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
	//		};
	//		glGenVertexArrays(1, &wallVAO);
	//		glGenBuffers(1, &wallVBO);
	//		glBindVertexArray(wallVAO);
	//		glBindBuffer(GL_ARRAY_BUFFER, wallVBO);
	//		glBufferData(GL_ARRAY_BUFFER, sizeof(wallVertice), &wallVertice, GL_STATIC_DRAW);
	//		glEnableVertexAttribArray(0);
	//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)0);
	//		glEnableVertexAttribArray(1);
	//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//		glEnableVertexAttribArray(2);
	//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	//		glEnableVertexAttribArray(3);
	//		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	//		glEnableVertexAttribArray(4);
	//		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(11 * sizeof(GLfloat)));
	//	}
	//	glBindVertexArray(wallVAO);
	//	glDrawArrays(GL_TRIANGLES, 0, 6);
	//	glBindVertexArray(0);

	//}
	//void renderScene(Shader &shader) {
	//	glm::mat4 model = glm::mat4(1.0f);
	//	model = glm::scale(model, glm::vec3(10.0));
	//	shader.setMat4("model", model);
	//	glDisable(GL_CULL_FACE);
	//	shader.setInt("reverse_normals", 1);
	//	renderCube();
	//	shader.setInt("reverse_normals", 0);
	//	glEnable(GL_CULL_FACE);

	//	model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(4.0f, -3.5f, 0.0));
	//	shader.setMat4("model", model);
	//	renderCube();
	//	model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(2.0f, 3.0f, 1.0));
	//	model = glm::scale(model, glm::vec3(1.5));
	//	shader.setMat4("model", model);
	//	renderCube();
	//	model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(-3.0f, -1.0f, 0.0));
	//	shader.setMat4("model", model);
	//	renderCube();
	//	model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(-1.5f, 1.0f, 1.5));
	//	shader.setMat4("model", model);
	//	renderCube();
	//	model = glm::mat4(1.0f);
	//	model = glm::translate(model, glm::vec3(-1.5f, 2.0f, -3.0));
	//	model = glm::rotate(model, glm::radians(60.0f), glm::normalize(glm::vec3(1.0, 0.0, 1.0)));
	//	model = glm::scale(model, glm::vec3(1.5));
	//	shader.setMat4("model", model);
	//	renderCube();
	//}
}