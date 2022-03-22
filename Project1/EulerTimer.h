#include<windows.h>
#include<mmsystem.h>
//多媒体相关API
#include"EulerSystem.h"
namespace EulerEngine {
	class EulerTimer {
	private:
		double FPS;
		double Time;
		double DeltaTime;
		double LastTime;
		double FrameCount;
		double TimeStart;
		double LastFPSTime;

		void InitGameTime() {
			FPS = 0;
			Time = 0;
			DeltaTime = 0;
			LastTime = 0;
			FrameCount = 0;
			LastFPSTime = 0;
			TimeStart = timeGetTime();
		}
		double GetGamePlayTime() {
			return (timeGetTime() - TimeStart);
		}
		void UpdateFps() {
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
	};
}