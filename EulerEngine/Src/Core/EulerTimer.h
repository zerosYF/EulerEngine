#pragma once
#include<windows.h>
#include<mmsystem.h>
//多媒体相关API
namespace EulerEngine {
	class TimerSystem{
	private:
		unsigned int m_FPS{0};
		double m_Time{ 0 };
		double m_DeltaTime{ 0 };
		double m_LastTime{ 0 };
		double m_FrameCount{ 0 };
		double m_LastFPSTime{ 0 };
		double m_TimeStart;
	public:
		TimerSystem() = default;
		~TimerSystem();
		void Initialize();
		void clear();
		double GetGamePlayTime();
		void updateFps();
		double GetDeltaTime() const{
			return m_DeltaTime;
		}
		unsigned int GetFPS() const {
			return m_FPS;
		}
	};
}