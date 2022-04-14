#pragma once
#include"EulerControl.h"
#include<GLFW/glfw3.h>
#include<iostream>
using namespace std;
namespace EulerEngine {
	class GLWindowManager {
	private:
		static GLWindowManager* _instance;
		float EULER_WIDTH = 800.0f;
		float EULER_HEIGHT = 600.0f;
	public:
		GLFWwindow* window;
	private:
		GLWindowManager() {
			glfwConfig();
			glfwWindowInit();
			glfwInputInit();
		}
		~GLWindowManager() {
			delete _instance;
		}
	public:
		static GLWindowManager* GetInstance() {
			if (_instance == NULL) {
				_instance = new GLWindowManager();
			}
			return _instance;
		}
		void glfwConfig() {
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}
		void glfwWindowInit() {
			window =
				glfwCreateWindow(EULER_WIDTH, EULER_HEIGHT, "euler forever", NULL, NULL);
			if (window == NULL) {
				cout << "what fuck" << endl;
				glfwTerminate();
			}
			glfwMakeContextCurrent(window);
		}
		void glfwInputInit() {
			glfwSetFramebufferSizeCallback(window, frameBuffer_size_Callback);
			glfwSetCursorPosCallback(window, mouse_Callback);
			glfwSetScrollCallback(window, scroll_Callback);
			glfwSetKeyCallback(window, key_Callback);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	};
	GLWindowManager* GLWindowManager::_instance = NULL;
}