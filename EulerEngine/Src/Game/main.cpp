#include"../../Studio/imgui.h"
#include"../../Studio/GLRender/imgui_impl_glfw.h"
#include"../../Studio/GLRender/imgui_impl_opengl3.h"
#include"EulerGame.h"
int main() {
	EulerGame game;
	game.Update();
	return 0;
}