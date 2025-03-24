#pragma once
namespace EulerEngine {
	class TimerSystem {
	private:
		static unsigned int m_FPS;
		static double m_Time;
		static double m_DeltaTime;
		static double m_LastTime;
		static double m_FrameCount;
		static double m_LastFPSTime;
	public:
		static void Tick();
		static double GetTime() {return m_Time;}
		static double GetDeltaTime() {return m_DeltaTime;}
		static int GetFPS() {return m_FPS;}
	};
}