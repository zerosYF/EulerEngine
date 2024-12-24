#include"gkpch.h"
#include<GutKink.h>
class ExampleLayer : public EulerEngine::EulerLayer {
public:
	void OnUpdate() override{
		if (EulerEngine::InputSystem::IsKeyDown(KINK_KEY_TAB)) {
			KINK_INFO("Tab key is pressed!");
		}
	}
	void OnEvent(EulerEngine::Event& event) override {
		if (event.GetEventType() == EulerEngine::EventType::KINK_KEY_PRESSED) {
			EulerEngine::KeyPressedEvent& e = (EulerEngine::KeyPressedEvent&)event;
			KINK_TRACE("{0}",(char)e.GetKeyCode());
		}
	}
};
class Sandbox : public EulerEngine::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {
	}
};
EulerEngine::Application* EulerEngine::CreateApplication() {
	return new Sandbox();
}