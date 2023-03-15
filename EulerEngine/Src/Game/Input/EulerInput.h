#pragma once
#include"../../Math/EulerMath.h"
namespace EulerEngine {
	enum GameCmd :unsigned int {
		forward = 1 << 0,
		backward = 1 << 1,
		left = 1 << 2,
		right = 1 << 3,
		jump = 1 << 4,
	};
	extern unsigned int i_complement_control_cmd;
	class InputSystem {
	public:
		double m_deltaX{0};
		double m_deltaY{0};
		float m_deltaYaw{0};
		float m_deltaPitch{0};

		void onKey(int key,int scanCode,int action,int mode);
		void onCursorPos(double currentX,double currentY);
		void initialize();
		void update();
		void clear();
	private:
		double m_lastX{0};
		double m_lastY{0};
		unsigned int m_game_cmd{0};
		void onKeyInGameMode(int key,int scanCode,int action,int mode);
		void calCursorDeltaAngles();
	};
}
