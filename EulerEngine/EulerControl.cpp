#include"EulerControl.h"
using namespace EulerEngine;
//void doMovement(Camera &camera) {
//	if (keys[GLFW_KEY_W]) {
//		camera.ProcessKeyboard(FORWARD);
//	}
//	if (keys[GLFW_KEY_A]) {
//		camera.ProcessKeyboard(LEFT);
//	}
//	if (keys[GLFW_KEY_S]) {
//		camera.ProcessKeyboard(BACKWARD);
//	}
//	if (keys[GLFW_KEY_D]) {
//		camera.ProcessKeyboard(RIGHT);
//	}
//}
//void frameBuffer_size_Callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//void key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	}
//	if (key >= 0 && key <= 1024) {
//		if (action == GLFW_PRESS) {
//			keys[key] = true;
//		}
//		else if (action == GLFW_RELEASE) {
//			keys[key] = false;
//			keysPressed[key] = false;
//
//		}
//	}
//}
//void mouse_Callback(GLFWwindow *window, double xpos, double ypos) {
//	if (firstMouse) {
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos;
//
//	lastX = xpos;
//	lastY = ypos;
//}
//void scroll_Callback(GLFWwindow *window, double xoffset, double yoffset) {
//}