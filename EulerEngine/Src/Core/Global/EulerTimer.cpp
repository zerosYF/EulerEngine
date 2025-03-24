#include "gkpch.h"
#include"EulerTimer.h"
#include<GLFW/glfw3.h>
namespace EulerEngine {
	unsigned int TimerSystem::m_FPS = 0;
	double TimerSystem::m_Time = 0;
	double TimerSystem::m_DeltaTime = 0;
	double TimerSystem::m_LastTime = 0;
	double TimerSystem::m_FrameCount = 0;
	double TimerSystem::m_LastFPSTime = 0;
	void TimerSystem::Tick() {
		m_Time = glfwGetTime();
		m_DeltaTime = m_Time - m_LastTime;
		m_LastTime = m_Time;
		if (m_Time - m_LastFPSTime > 1.0f) {
			m_LastFPSTime = m_Time;
			m_FPS = m_FrameCount;
			m_FrameCount = 0;
		}
		else {
			m_FrameCount++;
		}
	}
}