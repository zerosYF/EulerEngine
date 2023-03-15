#include"EulerGame.h"
#include"../Core/EulerTimer.h"
#include"../Render/OpenGL/GLShader.h"
#include"../Render/GLObjects/GLCube.h"
#include"../Render/GLObjects/GLSquare.h"
#include"../Render/OpenGL/GLCamera.h"
#include"../Render/OpenGL/GLModel.h"
#include"Context/EulerContext.h"


namespace EulerEngine {
	bool g_is_editor_mode{ false };
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
	void EulerGame::startEngine() {
		g_global_context.startSystems();
		g_global_context.initObject();
	}
	void EulerGame::shutdownEngine() {
		g_global_context.shutdownSystems();
	}
	void EulerGame::run() {
		std::shared_ptr<WindowSystem> window_sys = g_global_context.m_window_system;
		while (!window_sys->ShouldClose()) {
			updateOneFrame();
		}
	}
	void EulerGame::updateOneFrame() {
		double deltaTime = g_global_context.m_timer_system->GetDeltaTime();
		logicUpdate(deltaTime);
		g_global_context.m_timer_system->updateFps();
		g_global_context.m_render_system->DataLogic2Render();
		rendererUpdate(deltaTime);
	}
	void EulerGame::logicUpdate(double deltaTime) {
		g_global_context.m_world_mgr->update(deltaTime);
		g_global_context.m_input_system->update();
	}
	void EulerGame::rendererUpdate(double deltaTime) {
		g_global_context.m_render_system->update(deltaTime);
	}
}




