#pragma once
#include<string>
#ifndef GAME
namespace EulerEngine {
	extern bool g_is_editor_mode;
	class EulerGame {
	public:
		EulerGame() = default;
		void startEngine();
		void shutdownEngine();
		void clear();
		void run();
		bool isQuit() const { return m_isquit; }

	protected:
		bool m_isquit{ false };
	protected:
		void logicUpdate(double deltaTime);
		void rendererUpdate(double deltaTime);
		void updateOneFrame();
	};
}
#endif