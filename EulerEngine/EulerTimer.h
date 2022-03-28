#pragma once
#include<windows.h>
#include<mmsystem.h>
//多媒体相关API
namespace EulerEngine {
	class TimerManager {
	private:
		static TimerManager *_instance;
		double FPS;
		double Time;
		double DeltaTime;
		double LastTime;
		double FrameCount;
		double TimeStart;
		double LastFPSTime;
		TimerManager() {}
		~TimerManager() {
			delete _instance;
		}
	public:
		static TimerManager* GetInstance() {
			if (_instance == NULL) {
				_instance = new TimerManager();
			}
			return _instance;
		}
		inline void InitGameTime() {
			FPS = 0;
			Time = 0;
			DeltaTime = 0;
			LastTime = 0;
			FrameCount = 0;
			LastFPSTime = 0;
			TimeStart = timeGetTime();
		}
		inline double GetGamePlayTime() {
			return (timeGetTime() - TimeStart);
		}
		inline void UpdateFps() {
			Time = this->GetGamePlayTime()*0.001;
			DeltaTime = Time - LastTime;
			LastTime = Time;
			if (Time - LastFPSTime > 1.0f) {
				LastFPSTime = Time;
				FPS = FrameCount;
				FrameCount = 0;
			}
			else {
				FrameCount++;
			}
		}
	public:
		inline double GetDeltaTime() {
			return DeltaTime;
		}
	};
}