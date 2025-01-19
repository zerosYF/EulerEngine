#include"gkpch.h"
#include"GLContext.h"
#include<glfw/glfw3.h>
#include<glad/glad.h>
#include"Core/Logs/EulerLog.h"
namespace EulerEngine {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle):m_WindowHandle(windowHandle)
	{
		
	}
	void OpenGLContext::Initialize()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KINK_CORE_ASSERT(status, "Failed to intialize Glad!");
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}