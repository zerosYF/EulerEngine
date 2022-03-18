#include"Input.h"
Input::Input() {
}

void Input::doMovement() {
	if (keys[GLFW_KEY_W]) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (keys[GLFW_KEY_A]) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (keys[GLFW_KEY_S]) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (keys[GLFW_KEY_D]) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	if (keys[GLFW_KEY_SPACE] && !keysPressed[GLFW_KEY_SPACE]) {
		shadows = !shadows;
		keysPressed[GLFW_KEY_SPACE] = true;
	}
};
// ÒÆ¶¯
void Input::frameBuffer_size_Callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
// ¼üÅÌ
void Input::key_Callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key <= 1024) {
		if (action == GLFW_PRESS) {
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			keys[key] = false;
			keysPressed[key] = false;

		}
	}
}
// Êó±ê
void Input::mouse_Callback(GLFWwindow *window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// »¬ÂÖ
void Input::scroll_Callback(GLFWwindow *window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}
