#include"EulerGame.h"
#include"EulerTimer.h"
#include"GLRenderManager.h"
#include"GLWindowManager.h"
#include"GLShader.h"
#include"GLCube.h"
#include"GLSourceManager.h"

using namespace std;
using namespace EulerEngine;
void EulerGame::Update() {
	TimerManager::GetInstance()->InitGameTime();
	GLFWwindow* window = GLWindowManager::GetInstance()->window;
	GLRenderManager::GetInstance()->RenderConfig();

	SourceManager::GetInstance()->loadShader("sss","Normal.vertex", "Normal.fragment");

	CubeRender cube;

	SourceManager::GetInstance()->loadTexture("mytextures/wood.png","wood");
	SourceManager::GetInstance()->loadTexture("mytextures/roadtexture.jpg","container");

	SourceManager::GetInstance()->getShader("sss").use();
	SourceManager::GetInstance()->getShader("sss").setInt("texture1",0);
	SourceManager::GetInstance()->getShader("sss").setInt("texture2",1);

	Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	while (!(glfwWindowShouldClose(window))) {
		// ��ʱ�����£�
		TimerManager::GetInstance()->UpdateFps();
		// INPUT
		ProcessInput(window,camera);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glActiveTexture(GL_TEXTURE0);
		SourceManager::GetInstance()->getTexture("wood").bind();
		glActiveTexture(GL_TEXTURE1);
		SourceManager::GetInstance()->getTexture("container").bind();

		SourceManager::GetInstance()->getShader("sss").use();
		float aspect = GLRenderManager::GetInstance()->GetAspect();
		glm::mat4 projection = 
			glm::perspective(glm::radians(camera->Fov_Angle),aspect,0.1f,100.0f);
		SourceManager::GetInstance()->getShader("sss").setMat4("projection",projection);
		glm::mat4 view = camera->GetViewMatrix();
		SourceManager::GetInstance()->getShader("sss").setMat4("view",view);
		
		glm::mat4 model = glm::mat4(1.0f);
		cube.Render(SourceManager::GetInstance()->getShader("sss"),model);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	cube.Release();
	glfwTerminate();
}
int main() {
	EulerGame game;
	game.Update();
	return 0;
}




