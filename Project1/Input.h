#pragma once
#include<GLFW/glfw3.h>
#include"cCamera.h"
#include"door.h"
class Input {
public:
	bool  keys[1024];
	bool keysPressed[1024];
	bool firstMouse = true;
	float lastX = WIDTH / 2.0f;
	float lastY = HEIGHT / 2.0f;

	Input();
	void  doMovement();
	void  frameBuffer_size_Callback(GLFWwindow* window, int width, int height);
	void  key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	void mouse_Callback(GLFWwindow *window, double xpos, double ypos);
	void  scroll_Callback(GLFWwindow *window, double xoffset, double yoffset);

};