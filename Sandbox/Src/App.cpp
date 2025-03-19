#include<GutKink.h>
#include<GutKink/EntryPoint.h>
#include"TestLayer.h"
#include"_2DLayer.h"

class Sandbox : public EulerEngine::Application {
public:
	Sandbox(const EulerEngine::ApplicationSpecification& spec): Application(spec) {
		//PushLayer(new TestLayer());
		PushLayer(new _2DLayer());
	}
	~Sandbox() {
	}
};
EulerEngine::Application* EulerEngine::CreateApplication(ApplicationCommandLineArgs args) {
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.CmdArgs = args;
	return new Sandbox(spec);
}