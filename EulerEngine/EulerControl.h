#pragma once
#include<GLFW/glfw3.h>
namespace EulerEngine {
	bool keys[1024];
	bool keysPressed[1024];
	bool firstMouse = true;
	double lastX = 800.0f / 2.0f;
	double lastY = 600.0f / 2.0f;
	void frameBuffer_size_Callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
	void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		if (key >= 0 && key <= 1024) {
			if (action == GLFW_PRESS) {
				keys[key] = true;
			}
			else if (action == GLFW_RELEASE) {
				keys[key] = false;
				keysPressed[key] = false;

			}
		}
	}
	void mouse_Callback(GLFWwindow *window, double xpos, double ypos) {
		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}
		double xoffset = xpos - lastX;
		double yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;
	}
	void scroll_Callback(GLFWwindow *window, double xoffset, double yoffset) {
	
	}
}
