#pragma once
#include"GLControl.h"
#include<GLFW/glfw3.h>
#include<iostream>

#include"../../Studio/imgui.h"
#include"../../Studio/GLRender/imgui_impl_glfw.h"
#include"../../Studio/GLRender/imgui_impl_opengl3.h"

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

			glfwSwapInterval(1); // Enable vsync

			//imgui
			// Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

			// Setup Dear ImGui style
			ImGui::StyleColorsDark();
			//ImGui::StyleColorsClassic();

			// Setup Platform/Renderer backends
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 330");
		}
		void glfwInputInit() {
			//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	};
	GLWindowManager* GLWindowManager::_instance = NULL;
}