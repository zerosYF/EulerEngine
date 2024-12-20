#include"gkpch.h"
#include<GutKink.h>
class Sandbox : public EulerEngine::Application {
public:
	Sandbox() {
		PushLayer(new EulerEngine::ImGuiLayer());
	}
	~Sandbox() {
	}
};
EulerEngine::Application* EulerEngine::CreateApplication() {
	return new Sandbox();
}