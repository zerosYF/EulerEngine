#include"EulerWindow.h"
#include<iostream>
namespace EulerEngine {
	WindowSystem::~WindowSystem() {
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
	void WindowSystem::Initialize(WindowInfo create_info) {
		glViewport(0, 0, create_info.width, create_info.height);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_NOTEQUAL, 1, 0xff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (!glfwInit()) {
			std::cout << "GLFW initialize error" << std::endl;
			return;
		}
		m_info = create_info;
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(m_info.width,m_info.height,m_info.title,nullptr,nullptr);
		if (!m_window) {
			std::cout << "window initialize error" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1);
		setCallback();
	}
	void WindowSystem::PollEvents() const{
		glfwPollEvents();
	}
	bool WindowSystem::ShouldClose() const {
		return glfwWindowShouldClose(m_window);
	}
	GLFWwindow* WindowSystem::getWindow() const{
		return m_window;
	}
	float WindowSystem::getWindowHeight() const {
		return m_info.height;
	}
	float WindowSystem::getWIndowWidth() const {
		return m_info.width;
	}
}