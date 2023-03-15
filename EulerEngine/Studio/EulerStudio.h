#pragma once
#include<GLFW/glfw3.h>
#include<iostream>

#include"imgui/imgui.h"
#include"imgui/GLRender/imgui_impl_glfw.h"
#include"imgui/GLRender/imgui_impl_opengl3.h"

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
			glfwWindowInit();
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
		void glfwWindowInit() {
			
			//imgui
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::StyleColorsDark();

			// Setup Platform/Renderer backends
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 330");
		}   
		void StudioUIRender() {
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			ImGui::Begin("Hello, world!");
			ImGui::End();
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
	};
	GLWindowManager* GLWindowManager::_instance = NULL;
}