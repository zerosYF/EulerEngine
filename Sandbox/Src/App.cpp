#include<GutKink.h>
#include<GutKink/EntryPoint.h>
#include"TestLayer.h"
class Sandbox : public EulerEngine::Application {
public:
	Sandbox() {
		PushLayer(new TestLayer());
	}
	~Sandbox() {
	}
};
EulerEngine::Application* EulerEngine::CreateApplication() {
	return new Sandbox();
}