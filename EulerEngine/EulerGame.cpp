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

	Shader shader = SourceManager::GetInstance()->
		loadShader("sss","Normal.vertex", "Normal.fragment");

	CubeRender cube;

	Texture2D texture2d;
	int width, height,channel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("mytextures/container2.png",&width,&height,&channel,0);
	if (data) {
		texture2d.generate(width, height, channel, data);
	}
	else {
		cout << "图片加载失败" << endl;
	}
	stbi_image_free(data);

	shader.use();
	shader.setInt("texture1",0);

	Camera *camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	while (!(glfwWindowShouldClose(window))) {
		// 定时器更新；
		TimerManager::GetInstance()->UpdateFps();
		// INPUT
		ProcessInput(window,camera);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glActiveTexture(GL_TEXTURE0);
		texture2d.bind();

		shader.use(); 
		float aspect = GLRenderManager::GetInstance()->GetAspect();
		glm::mat4 projection = 
			glm::perspective(glm::radians(camera->Fov_Angle),aspect,0.1f,100.0f);
		shader.setMat4("projection",projection);
		glm::mat4 view = camera->GetViewMatrix();
		shader.setMat4("view",view);
		
		glm::mat4 model = glm::mat4(1.0f);
		cube.Render(shader,model);

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




