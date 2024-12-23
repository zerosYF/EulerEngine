#include "gkpch.h"
#include "WinInput.h"
#include "GutKink\Application.h"
#include<GLFW/glfw3.h>
namespace EulerEngine {

	InputSystem* InputSystem::s_Instance = new WinInput();

	bool WinInput::I_IsKeyDown(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWIndow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WinInput::I_IsMouseBtnDown(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWIndow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	std::pair<double, double> WinInput::I_GetCursorPosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWIndow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return {xPos, yPos};
	}
}