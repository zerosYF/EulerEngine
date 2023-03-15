#pragma once
#include<GLFW/glfw3.h>
#include"../OpenGL/GLCamera.h"
namespace EulerEngine {
	/*bool firstMouse = true;
	double lastX = 800.0f / 2.0f;
	double lastY = 600.0f / 2.0f;
	void CursorInput(GLFWwindow* window, Camera *camera) {
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		if (firstMouse) {
			lastX = xPos;
			lastY = yPos;
			firstMouse = false;
		}
		double xoffset = xPos - lastX;
		double yoffset = lastY - yPos;

		lastX = xPos;
		lastY = yPos;
		camera->ProcessMouseMovement(xoffset, yoffset);
	}
	void ProcessInput(GLFWwindow* window,Camera* camera) {
		if (glfwGetKey(window, GLFW_KEY_W)) {
			camera->ProcessKeyboard(FORWARD);
		}
		if (glfwGetKey(window, GLFW_KEY_A)) {
			camera->ProcessKeyboard(LEFT);
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			camera->ProcessKeyboard(BACKWARD);
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			camera->ProcessKeyboard(RIGHT);
		}
		CursorInput(window,camera);
	}*/
}
