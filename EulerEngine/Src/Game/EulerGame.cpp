#include"EulerGame.h"
#include"../Core/EulerTimer.h"
#include"../Render/OpenGL/GLRenderManager.h"
#include"../Render/OpenGL/GLWindowManager.h"
#include"../Render/OpenGL/GLShader.h"
#include"../Render/OpenGL/GLCube.h"
#include"../Render/OpenGL/GLSourceManager.h"
#include"../Render/OpenGL/GLCamera.h"

using namespace std;
using namespace EulerEngine;
void EulerGame::Update() {
	TimerManager::GetInstance()->InitGameTime();
	GLFWwindow* window = GLWindowManager::GetInstance()->window;
	GLRenderManager::GetInstance()->RenderConfig();

	Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	CubeRender cube;
	SourceManager::GetInstance()
		->loadShader("box","Shaders/Light/common.vert", "Shaders/Light/common.frag");
	SourceManager::GetInstance()->loadTexture("Assets/mytextures/wood.png","wood");
	SourceManager::GetInstance()->loadTexture("Assets/mytextures/roadtexture.jpg","container");
	SourceManager::GetInstance()->getShader("box").use();
	SourceManager::GetInstance()->getShader("box").setInt("texture1",0);
	SourceManager::GetInstance()->getShader("box").setInt("texture2",1);

	CubeRender light;
	SourceManager::GetInstance()
		->loadShader("light", "Shaders/Light/light.vert", "Shaders/Light/light.frag");
	SourceManager::GetInstance()->getShader("light").use();
	SourceManager::GetInstance()->getShader("light").setVec3("lightColor",glm::vec3(1.0f,1.0f,1.0f));
	glm::vec3 lightPos(1.5f,1.0f,1.0f);
	glm::vec3 lightColor(1.0f,1.0f,1.0f);

	while (!(glfwWindowShouldClose(window))) {
		// 定时器更新；
		TimerManager::GetInstance()->UpdateFps();
		// INPUT
		ProcessInput(window,camera);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glActiveTexture(GL_TEXTURE0);
		SourceManager::GetInstance()->getTexture("wood").bind();
		glActiveTexture(GL_TEXTURE1);
		SourceManager::GetInstance()->getTexture("container").bind();

		float aspect = GLRenderManager::GetInstance()->GetAspect();
		glm::mat4 projection = 
			glm::perspective(glm::radians(camera->Fov_Angle),aspect,0.1f,100.0f);
		glm::mat4 view = camera->GetViewMatrix();

		glm::mat4 model = glm::mat4(1.0f);
		cube.Render(
			SourceManager::GetInstance()->getShader("box"),
			model,view,projection,lightPos,camera->Position,lightColor);

		model = glm::mat4(1.0f);
		model = glm::translate(model,lightPos);
		model = glm::scale(model,glm::vec3(0.2f));
		light.Render(
			SourceManager::GetInstance()->getShader("light"),
			model,view,projection);

		GLWindowManager::GetInstance()->StudioUIRender();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	cube.Release();
	glfwTerminate();
}




