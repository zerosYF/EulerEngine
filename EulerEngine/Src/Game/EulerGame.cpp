#include "gkpch.h"
#include"EulerGame.h"
#include"../Core/EulerTimer.h"
#include"../Render/OpenGL/GLShader.h"
#include"../Render/GLObjects/GLCube.h"
#include"../Render/GLObjects/GLSquare.h"
#include"../Render/OpenGL/GLCamera.h"
#include"../Render/OpenGL/GLModel.h"


namespace EulerEngine {
	/*bool g_is_editor_mode{ false };
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
	}*/
}




