#pragma once
#include<GLFW/glfw3.h>
#include<functional>
#include<vector>
namespace EulerEngine {
	struct  WindowInfo
	{
		float width = 1280.0f;
		float height = 900.0f;
		const char* title{"EulerEngine"};
		bool isFullScreen = false;
	};
	class WindowSystem {
	public:
		WindowSystem() = default;
		~WindowSystem();
		void Initialize(WindowInfo);
		void PollEvents() const;
		bool ShouldClose() const;
		GLFWwindow* getWindow() const;
		float getWIndowWidth() const;
		float getWindowHeight() const;

		bool getFocusMode() const {
			return  m_isFocusMode;
		}
		void setFocusMode(bool mode) {
			m_isFocusMode = mode;
			glfwSetInputMode(m_window,GLFW_CURSOR,mode?GLFW_CURSOR_DISABLED:GLFW_CURSOR_NORMAL);
		}

		typedef std::function<void()> onResetFunc;
		typedef std::function<void(int, int, int, int)> onKeyFunc;
		typedef std::function<void(int, int, int)> onClickFunc;
		typedef std::function<void(double, double)> onCursorPosFunc;
		typedef std::function<void(double, double)> onScrollFunc;
		typedef std::function<void(int, int)> onWindowSizeFunc;
		typedef std::function<void()> onWindowCloseFunc;

		void registerResetFunc(onResetFunc func) {
			m_resetFuncs.push_back(func);
		}
		void registerKeyFunc(onKeyFunc func) {
			m_keyFuncs.push_back(func);
		}
		void registerClickFunc(onClickFunc func) {
			m_clickFuncs.push_back(func);
		}
		void registerCursorPosFunc(onCursorPosFunc func) {
			m_cursorposFuncs.push_back(func);
		}
		void registerScrollFunc(onScrollFunc func) {
			m_scrollFuncs.push_back(func);
		}
		void registerWIndowSizeFunc(onWindowSizeFunc func) {
			m_windowsizeFuncs.push_back(func);
		}
		void registerWindowCloseFunc(onWindowCloseFunc func) {
			m_windowcloseFuncs.push_back(func);
		}
		
	protected:
		static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode) {
			WindowSystem* userptr = (WindowSystem*)glfwGetWindowUserPointer(window);
			if (userptr) {
				for (auto& func : userptr->m_keyFuncs) {
					func(key, scanCode, action, mode);
				}
			}
		}
		static void clickCallback(GLFWwindow* window, int button,int action,int mode) {
			WindowSystem* userptr = (WindowSystem*)glfwGetWindowUserPointer(window);
			if (userptr) {
				for (auto& func : userptr->m_clickFuncs) {
					func(button,action,mode);
				}
			}
		}
		static void cursorposCallback(GLFWwindow* window,double xPos,double yPos) {
			WindowSystem* userptr = (WindowSystem*)glfwGetWindowUserPointer(window);
			if (userptr) {
				for (auto& func : userptr->m_cursorposFuncs) {
					func(xPos,yPos);
				}
			}
		}
		static void scrollCallback(GLFWwindow* window, double xOffset,double yOffset) {
			WindowSystem* userptr = (WindowSystem*)glfwGetWindowUserPointer(window);
			if (userptr) {
				for (auto& func : userptr->m_scrollFuncs) {
					func(xOffset,yOffset);
				}
			}
		}
		static void windowsizeCallback(GLFWwindow* window,int width,int height) {
			WindowSystem* userptr = (WindowSystem*)glfwGetWindowUserPointer(window);
			if (userptr) {
				for (auto& func : userptr->m_windowsizeFuncs) {
					func(width,height);
				}
			}
		}
		static void windowcloseCallback(GLFWwindow* window) {
			glfwSetWindowShouldClose(window,true);
		}
		
	private:
		GLFWwindow *m_window = nullptr;
		WindowInfo m_info;
		bool m_isFocusMode = false;

		std::vector<onResetFunc> m_resetFuncs;
		std::vector<onKeyFunc> m_keyFuncs;
		std::vector<onClickFunc> m_clickFuncs;
		std::vector<onCursorPosFunc> m_cursorposFuncs;
		std::vector<onScrollFunc> m_scrollFuncs;
		std::vector<onWindowSizeFunc> m_windowsizeFuncs;
		std::vector<onWindowCloseFunc> m_windowcloseFuncs;

		void setCallback() {
			glfwSetWindowUserPointer(m_window,this);
			glfwSetKeyCallback(m_window,keyCallback);
			glfwSetMouseButtonCallback(m_window,clickCallback);
			glfwSetCursorPosCallback(m_window,cursorposCallback);
			glfwSetScrollCallback(m_window,scrollCallback);
			glfwSetWindowSizeCallback(m_window,windowsizeCallback);
			glfwSetWindowCloseCallback(m_window,windowcloseCallback);
		}
	};
}