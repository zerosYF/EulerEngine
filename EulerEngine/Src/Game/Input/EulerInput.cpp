#include"EulerInput.h"
#include<GLFW/glfw3.h>
#include"../Context/EulerContext.h"
#include"../../Math/EulerMath.h"
using namespace placeholders;
namespace EulerEngine {
	unsigned int i_complement_control_cmd = 0xFFFFFFFF;
	void InputSystem::onKey(int key,int scanCode,int action,int mode) {
		onKeyInGameMode(key,scanCode,action,mode);
	}
	void InputSystem::onKeyInGameMode(int key,int scanCode,int action,int mode) {
		if (action == GLFW_PRESS) {
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
				break;
			case GLFW_KEY_W:
				break;
			case GLFW_KEY_A:
				break;
			case GLFW_KEY_S:
				break;
			case GLFW_KEY_D:
				break;
			default:
				break;
			}
		}
		else if (action == GLFW_RELEASE) {
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
				break;
			case GLFW_KEY_W:
				break;
			case GLFW_KEY_A:
				break;
			case GLFW_KEY_S:
				break;
			case GLFW_KEY_D:
				break;
			default:
				break;
			}
		}
	}
	void InputSystem::onCursorPos(double currentX,double currentY) {
		if (g_global_context.m_window_system->getFocusMode()) {
			m_deltaX = m_lastX - currentX;
			m_deltaY = m_lastY - currentY;
		}
		m_lastX = currentX;
		m_lastY = currentY;
	}
	void InputSystem::clear() {
		m_deltaX = 0;
		m_deltaY = 0;
	}
	void InputSystem::calCursorDeltaAngles() {
		float width = g_global_context.m_window_system->getWIndowWidth();
		float height = g_global_context.m_window_system->getWindowHeight();
		if (width < 1.0f || height < 1.0f) {
			return;
		}
		std::shared_ptr<Camera> render_camera = g_global_context.m_render_system->getRenderCamera();
		float fov = render_camera->m_fovAngle;
		m_deltaYaw = (glm::radians(fov) / width)*fov;
		m_deltaPitch = (glm::radians(fov) / height)*fov;
	}
	void InputSystem::initialize() {
		std::shared_ptr<WindowSystem> windowSys = g_global_context.m_window_system;
		windowSys->registerKeyFunc(bind(&InputSystem::onKey,this,_1,_2,_3,_4));
		windowSys->registerCursorPosFunc(bind(&InputSystem::onCursorPos, this, _1, _2));
	}
	void InputSystem::update() {
		calCursorDeltaAngles();
	}
}