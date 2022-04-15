#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
using namespace std;
namespace EulerEngine {
	class GLRenderManager {
	private:
		static GLRenderManager* _instance;
		const float SCR_WIDTH = 600;
		const float SCR_HEIGHT = 600;
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
			glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		}
		float GetAspect() {
			return SCR_WIDTH / SCR_HEIGHT;
		}
	};
	GLRenderManager* GLRenderManager::_instance = NULL;
}