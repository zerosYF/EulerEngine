#include"WindowConfig.h"
#include<iostream>
using namespace EulerEngine;
using namespace std;
void GLRenderManager::glfwConfig() {
	glfwInit();
	//°æ±¾ºÅ3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
void GLRenderManager::glfwWindowInit() {
	window =
		glfwCreateWindow(EULER_WIDTH, EULER_HEIGHT, "euler forever", NULL, NULL);
	if (window == NULL) {
		cout << "what fuck" << endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
}
void GLRenderManager::glfwInputInit() {
	/*glfwSetFramebufferSizeCallback(window, frameBuffer_size_Callback);
	glfwSetCursorPosCallback(window, mouse_Callback);
	glfwSetScrollCallback(window, scroll_Callback);
	glfwSetKeyCallback(window, key_Callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);*/
}
int GLRenderManager::gladInit() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "failed to init GLAD" << endl;
		return -1;
	}
	return 0;
}