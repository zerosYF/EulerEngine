#pragma once
namespace EulerEngine {
	class TimerSystem {
	private:
		unsigned int m_FPS{ 0 };
		double m_Time{ 0 };
		double m_DeltaTime{ 0 };
		double m_LastTime{ 0 };
		double m_FrameCount{ 0 };
		double m_LastFPSTime{ 0 };
	public:
		TimerSystem() = default;
		~TimerSystem() {}
		void Tick();
		double GetTime() const{return m_Time;}
		double GetDeltaTime() const{return m_DeltaTime;}
		unsigned int GetFPS() const {return m_FPS;}
	};
}