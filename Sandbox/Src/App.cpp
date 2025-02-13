#include<GutKink.h>
#include<GutKink/EntryPoint.h>
#include"TestLayer.h"
#include"_2DLayer.h"


class Sandbox : public EulerEngine::Application {
public:
	Sandbox() {
		PushLayer(new TestLayer());
		//PushLayer(new _2DLayer());
	}
	~Sandbox() {
	}
};
EulerEngine::Application* EulerEngine::CreateApplication() {
	return new Sandbox();
}