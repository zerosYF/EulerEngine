#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
using namespace std;
namespace EulerEngine {
	class GLRenderManager {
	private:
		static GLRenderManager* _instance;
		GLRenderManager() {
			gladInit();
		}
	public:
		static GLRenderManager* GetInstance() {
			if (_instance == nullptr) {
				_instance = new GLRenderManager();
			}
			return _instance;
		}
		void gladInit() {
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				cout << "failed to init GLAD" << endl;
			}
		}
		void RenderConfig() {
			glEnable(GL_DEPTH_TEST);
			glViewport(0, 0, 600, 600);
		}
	};
	GLRenderManager* GLRenderManager::_instance = NULL;
}