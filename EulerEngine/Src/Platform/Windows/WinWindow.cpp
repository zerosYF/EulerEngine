#include "gkpch.h"
#include"WinWIndow.h"
#include"Core/Logs/EulerLog.h"
#include"Core/Events/ApplicationEvent.h"
#include"Core/Events/KeyboardEvent.h"
#include"Core/Events/MouseEvent.h"
#include"Platform/OpenGL/GLContext.h"
namespace EulerEngine {
	static bool s_GLFWIntialized = false;

	EulerWindow* EulerWindow::Create(const WindowInfo& info) {
		return new WinWindow(info);
	}
	WinWindow::WinWindow(const WindowInfo& info) {
		Initialize(info);
	}
	WinWindow::~WinWindow() {
		ShutDown();
	}

	void WinWindow::Initialize(const WindowInfo& info) {
		m_Data.Title = info.Title;
		m_Data.Width = info.Width;
		m_Data.Height = info.Height;
		

		KINK_CORE_INFO("Create Window {0} ({1} {2})", info.Title, info.Width, info.Height);

		if (!s_GLFWIntialized) {
			int success = glfwInit();
			KINK_CORE_ASSERT(success, "Could not intialize GLFW!");
			s_GLFWIntialized = true;
		}

		m_Window = glfwCreateWindow((int)info.Width, (int)info.Height, m_Data.Title.c_str(), nullptr, nullptr);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Initialize();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetErrorCallback([](int code, const char* message) {
			KINK_CORE_ERROR("GLFW error {0}", code);
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowResizeEvent event(width, height);
			data.Callback(event);
			data.Width = width;
			data.Height = height;
		});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.Callback(event);
		});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scan_code, int action, int modes) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
					KeyPressedEvent event(key, 0);
					data.Callback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyReleasedEvent event(key);
					data.Callback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyPressedEvent event(key, 1);
					data.Callback(event);
					break;
				}
			}
		});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.Callback(event);
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int modes) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
				case GLFW_PRESS: {
					MouseButtonPressedEvent event(button);
					data.Callback(event);
					break;
				}
				case GLFW_RELEASE: {
					MouseButtonReleasedEvent event(button);
					data.Callback(event);
					break;
				}
			}
		});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event(xOffset, yOffset);
			data.Callback(event);
		});
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			if (FirstMouseMove) {
				LastMouseX = x;
				LastMouseY = y;
				FirstMouseMove = false;
			}

			double xOffset = x - LastMouseX;
			double yOffset = y - LastMouseY;
			LastMouseX = x;
			LastMouseY = y;
			MouseMovedEvent event(x, y, xOffset, yOffset);
			data.Callback(event);
		});
	}

	void WinWindow::ShutDown() {
		glfwDestroyWindow(m_Window);
	}
	void WinWindow::OnUpdate() {
		glfwPollEvents();
		
		m_Context->SwapBuffers();
	}
	void WinWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		}
		else {
			glfwSwapInterval(0);
		}
		m_Data.VSync = enabled;
	}
	bool WinWindow::IsVSync() const{
		return m_Data.VSync;
	}
}