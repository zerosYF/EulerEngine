#include"EulerGame.h"
#include"../Core/EulerTimer.h"
#include"../Render/OpenGL/GLRenderManager.h"
#include"../Render/OpenGL/GLWindowManager.h"
#include"../Render/OpenGL/GLShader.h"
#include"../Render/GLObjects/GLCube.h"
#include"../Render/OpenGL/GLSourceManager.h"
#include"../Render/OpenGL/GLCamera.h"
#include"../Render/OpenGL/GLModel.h"
#include"../Test/Test_Cube.h"
#include"../Test/Test_Stencil.h"

using namespace std;
using namespace EulerEngine;
glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
};
glm::vec3 plantPosition(0.0f, 0.0f, 0.0f);
void EulerGame::Update() {
	TimerManager::GetInstance()->InitGameTime();
	GLFWwindow* window = GLWindowManager::GetInstance()->window;
	GLRenderManager::GetInstance()->RenderConfig();

	Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	SourceManager::GetInstance()->loadShader("universal", "Shaders/Light/common.vert", "Shaders/Light/common.frag");

	Cube cube;
	SourceManager::GetInstance()->loadTexture("Assets/mytextures/container2.png", "wood");
	SourceManager::GetInstance()->loadTexture("Assets/mytextures/container2_specular.png", "container");
	cube.addTexture(SourceManager::GetInstance()->getTexture("wood"), DIFFUSE);
	cube.addTexture(SourceManager::GetInstance()->getTexture("container"), SPECULAR);
	TestStencilInit();

	EulerSpotLight* light3 = new EulerSpotLight();
	Shader lightShader3 = SourceManager::GetInstance()
		->loadShader("light3", "Shaders/Light/light.vert", "Shaders/Light/light.frag");
	light3->setShader(lightShader3);

	while (!(glfwWindowShouldClose(window))) {
		// 定时器更新；
		TimerManager::GetInstance()->UpdateFps();
		// INPUT
		ProcessInput(window,camera);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

		float aspect = GLRenderManager::GetInstance()->GetAspect();
		glm::mat4 projection = 
			glm::perspective(glm::radians(camera->Fov_Angle),aspect,0.1f,100.0f);
		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);

		light3->setTransform(camera->Position, glm::vec3(0.1f), glm::vec3(0.0f));
		light3->setDirection(camera->Front);
		light3->Render(model, view, projection);
		
		TestPlantRender(cube, model, view, projection, camera->Position, 0, NULL, 1, light3, 0, NULL);
		TestStencilRender(cube, model, view, projection, camera->Position,0, NULL, 1, light3, 0, NULL);

		GLWindowManager::GetInstance()->StudioUIRender();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}




