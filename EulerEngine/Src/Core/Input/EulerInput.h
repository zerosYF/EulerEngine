#pragma once
#include"Math/EulerMath.h"
#include"GutKink/Core.h"
#include"InputCodes.h"
namespace EulerEngine {
	extern unsigned int i_complement_control_cmd;
	class KINK_API InputSystem {
	public:

		inline static bool IsKeyDown(int keycode) { return s_Instance->I_IsKeyDown(keycode); }
		inline static bool IsMouseBtnDown(int button) { return s_Instance->I_IsMouseBtnDown(button); }
		inline static std::pair<double, double> GetCursorPosition() { return s_Instance->I_GetCursorPosition(); }
	protected:
		virtual bool I_IsKeyDown(int keycode) = 0;
		virtual bool I_IsMouseBtnDown(int button) = 0;
		virtual std::pair<double, double> I_GetCursorPosition() = 0;
	private:
		static InputSystem* s_Instance;
	};
}
