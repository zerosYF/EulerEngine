#pragma once
#include <GLFW/glfw3.h>
#include<glad/glad.h>
#include<vector>
#include "stb_image.h"
#include "door.h"
#include "cShader.h"
#include <vector>
using namespace std;
unsigned int addTexture(const char* path) {
	cout << path << endl;
	int width, height;
	int nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = 0;
	data = stbi_load(path, &width, &height, &nrChannels, 0);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 设置环绕，过滤方式;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
		return texture;
	}
	else {
		std::cout << "create texture failed" << std::endl;
		stbi_image_free(data);
		return -1;
	}
}

unsigned int loadCubemap(vector<std::string> faces) {
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	// 六面枚举贴图递增；
	for (int i = 0; i < faces.size(); i++) {
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else {
			std::cout << "cubemap出错了" << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return textureID;
}

unsigned int loadHDRmap(const char* path) {
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrComponents;
	float *data = stbi_loadf(path,&width,&height,&nrComponents,0);
	unsigned int hdrTexture;
	if (data) {
		glGenTextures(1,&hdrTexture);
		glBindTexture(GL_TEXTURE_2D,hdrTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB16F,width,height,0,GL_RGB,GL_FLOAT,data);
		stbi_image_free(data);
		return hdrTexture;
	}
	else {
		cout << "Failed to load HDR image" << endl;
		return -1;
	}
}

glm::mat4 *  Planet(unsigned int amount) {
	glm::mat4 *modelMatrices = new glm::mat4[amount];

	srand(glfwGetTime());
	float radius = 50.0;
	float offset = 2.5f;

	for (int i = 0; i < amount; i++) {
		glm::mat4 model = glm::mat4(1.0f);
		float angle = (float)i / (float)amount* 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) *radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle)*radius + displacement;
		model = glm::translate(model,glm::vec3(x,y,z));

		float scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model,glm::vec3(scale));

		float rotate = (rand() % 360);
		model = glm::rotate(model,rotate,glm::vec3(0.4f,0.6f,0.8f));

		modelMatrices[i] = model;
	}
	return modelMatrices;
}
