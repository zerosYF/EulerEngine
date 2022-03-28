#include"EulerMain.h"
#include"EulerTimer.h"
#include"WindowConfig.h"
#include"Test_SmartPointer.h"
using namespace std;
using namespace EulerEngine;
TimerManager* TimerManager::_instance = NULL;
GLRenderManager* GLRenderManager::_instance = NULL;
void EulerMain::Run() {
	TimerManager::GetInstance()->InitGameTime();
	GLFWwindow* window = GLRenderManager::GetInstance()->window;
	while (!(glfwWindowShouldClose(window))) {
		// ��ʱ�����£�
		TimerManager::GetInstance()->UpdateFps();

		//domovement();
	}
	glfwTerminate();
}
int main() {
	testfunc();
	return 0;
}




