#include"../../Editor/imgui.h"
#include"../../Editor/GLRender/imgui_impl_glfw.h"
#include"../../Editor/GLRender/imgui_impl_opengl3.h"
#include"EulerGame.h"
int main() {
	EulerGame game;
	game.Update();
	return 0;
}