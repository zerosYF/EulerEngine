#include"gkpch.h"
#include<GutKink.h>
class Sandbox : public EulerEngine::Application {
public:
	Sandbox() {
	}
	~Sandbox() {
	}
};
EulerEngine::Application* EulerEngine::CreateApplication() {
	return new Sandbox();
}