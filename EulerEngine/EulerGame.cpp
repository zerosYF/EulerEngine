#include"EulerGame.h"
#include"EulerTimer.h"
#include"GLRenderManager.h"
#include"GLWindowManager.h"
#include"GLShader.h"
#include"GLCube.h"
#include"GLSourceManager.h"
#include"GLCamera.h"

using namespace std;
using namespace EulerEngine;
void EulerGame::Update() {
	TimerManager::GetInstance()->InitGameTime();
	GLFWwindow* window = GLWindowManager::GetInstance()->window;
	GLRenderManager::GetInstance()->RenderConfig();

	Shader shader = SourceManager::GetInstance()->
		loadShader("sss","Normal.vertex", "Normal.fragment");

	CubeRender cube;

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

	while (!(glfwWindowShouldClose(window))) {
		// 定时器更新；
		TimerManager::GetInstance()->UpdateFps();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shader.use(); 
		float aspect = GLRenderManager::GetInstance()->GetAspect();
		glm::mat4 projection = 
			glm::perspective(glm::radians(camera.Fov_Angle),aspect,0.1f,100.0f);
		shader.setMat4("projection",projection);
		glm::mat4 view = camera.GetViewMatrix();
		shader.setMat4("view",view);
		
		cube.Render(shader);

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




