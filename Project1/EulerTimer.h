#include<MMSystem.h>
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

		void InitGameTime() {
			FPS = 0;
			Time = 0;
			DeltaTime = 0;
			LastTime = 0;
			FrameCount = 0;
			TimeStart = timeGetTime();
		}
		void GetGamePlayTime() {
			
		}
		void UpdateFps() {
		}
	};
}