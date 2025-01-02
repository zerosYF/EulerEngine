#pragma once
#include "Render/Context/EulerContext.h"
struct GLFWwindow;
namespace EulerEngine {
	class OpenGLContext : public EulerContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		void Initialize() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}