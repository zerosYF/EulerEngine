#include"EulerGame.h"
#include"EulerTimer.h"
#include"GLRenderManager.h"
#include"GLWindowManager.h"
#include"GLShader.h"
#include"GLBuffer.h"
#include"EulerCube.h"
#include"GLSourceManager.h"
using namespace std;
using namespace EulerEngine;
void EulerGame::Update() {
	TimerManager::GetInstance()->InitGameTime();
	GLFWwindow* window = GLWindowManager::GetInstance()->window;
	GLRenderManager::GetInstance()->RenderConfig();

	Shader shader = SourceManager::GetInstance()->
		loadShader("sss","Normal.vertex", "Normal.fragment");

	Cube cube;

	VBO vbo;
	vbo.BindVBO(CubeVertices);
	VAO vao;
	vao.BindVAO();
	cube.BindVAO();

	while (!(glfwWindowShouldClose(window))) {
		// 定时器更新；
		TimerManager::GetInstance()->UpdateFps();

		//shader.use();
	}
	glfwTerminate();
}
int main() {
	EulerGame game;
	game.Update();
	return 0;
}




