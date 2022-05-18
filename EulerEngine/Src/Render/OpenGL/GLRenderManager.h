#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
using namespace std;
namespace EulerEngine {
	class GLRenderManager {
	private:
		static GLRenderManager* _instance;
		const float SCR_WIDTH = 800;
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
			glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glEnable(GL_STENCIL_TEST);
			glStencilFunc(GL_NOTEQUAL,1,0xff);
			glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		}
		float GetAspect() {
			return SCR_WIDTH / SCR_HEIGHT;
		}
	};
	GLRenderManager* GLRenderManager::_instance = NULL;
}