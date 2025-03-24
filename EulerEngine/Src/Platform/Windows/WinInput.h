#pragma once
#include"Core/IO/EulerInput.h"
namespace EulerEngine {
	class WinInput :public InputSystem {
	protected:
		virtual bool I_IsKeyDown(int keycode) override;
		virtual bool I_IsMouseBtnDown(int button) override;
		virtual std::pair<double, double> I_GetCursorPosition() override;
	};
}