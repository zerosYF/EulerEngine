#include"EulerGame.h"
#include"../Core/EulerTimer.h"
#include"../Render/OpenGL/GLRenderManager.h"
#include"../Render/OpenGL/GLWindowManager.h"
#include"../Render/OpenGL/GLShader.h"
#include"../Render/GLObjects/GLCube.h"
#include"../Render/OpenGL/GLSourceManager.h"
#include"../Render/OpenGL/GLCamera.h"

using namespace std;
using namespace EulerEngine;
void EulerGame::Update() {
	TimerManager::GetInstance()->InitGameTime();
	GLFWwindow* window = GLWindowManager::GetInstance()->window;
	GLRenderManager::GetInstance()->RenderConfig();

	Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	Cube cube;
	glm::vec3 cubePos(0.0f, 0.0f, 0.0f);
	SourceManager::GetInstance()->loadShader("box","Shaders/Light/common.vert", "Shaders/Light/common.frag");
	cube.setShader(SourceManager::GetInstance()->getShader("box"));
	SourceManager::GetInstance()->loadTexture("Assets/mytextures/container2.png","wood");
	SourceManager::GetInstance()->loadTexture("Assets/mytextures/container2_specular.png","container");
	cube.addTexture(SourceManager::GetInstance()->getTexture("wood"),DIFFUSE);
	cube.addTexture(SourceManager::GetInstance()->getTexture("container"),SPECULAR);

	EulerPointLight light;
	glm::vec3 lightPos(1.5f, 1.0f, 1.0f);
	Shader lightShader = SourceManager::GetInstance()
		->loadShader("light", "Shaders/Light/light.vert", "Shaders/Light/light.frag");
	light.setShader(lightShader);

	while (!(glfwWindowShouldClose(window))) {
		// 定时器更新；
		TimerManager::GetInstance()->UpdateFps();
		// INPUT
		ProcessInput(window,camera);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float aspect = GLRenderManager::GetInstance()->GetAspect();
		glm::mat4 projection = 
			glm::perspective(glm::radians(camera->Fov_Angle),aspect,0.1f,100.0f);
		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);
		
		glm::vec3 color;
		color.x = sin(glfwGetTime() * 2.0f);
		color.y = sin(glfwGetTime() * 0.7f);
		color.z = sin(glfwGetTime() * 1.3f);
		light.setColor(color);

		cube.setTransform(cubePos,glm::vec3(1.0f),glm::vec3(0.0f));
		cube.Render(model,view,projection,camera->Position,light);

		light.setTransform(lightPos, glm::vec3(0.1f),glm::vec3(0.0f));
		light.Render(model,view,projection);

		GLWindowManager::GetInstance()->StudioUIRender();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	cube.Release();
	light.Release();
	glfwTerminate();
}




