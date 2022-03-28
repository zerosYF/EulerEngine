#pragma once
#include"EulerControl.h"
#include FT_FREETYPE_H
#include<GLFW/glfw3.h>
namespace EulerEngine {
	class GLRenderManager {
	private:
		static GLRenderManager* _instance;
	public:
		GLFWwindow* window;
	private:
		GLRenderManager() {
			glfwConfig();
			glfwWindowInit();
			glfwInputInit();
			gladInit();
		}
		~GLRenderManager() {
			delete _instance;
		}
	public:
		static GLRenderManager* GetInstance() {
			if (_instance == NULL) {
				_instance = new GLRenderManager();
			}
			return _instance;
		}
		void glfwConfig();
		void glfwWindowInit();
		void glfwInputInit();
		int gladInit();
	};
}