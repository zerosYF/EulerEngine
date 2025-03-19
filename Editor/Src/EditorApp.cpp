#include<GutKink.h>
#include<GutKink/EntryPoint.h>
#include"EditorLayer.h"
namespace EulerEngine {
	class EulerEditor : public EulerEngine::Application {
	public:
		EulerEditor(const ApplicationSpecification& spec):Application(spec) {
			PushLayer(new EditorLayer());
		}
		~EulerEditor() {
		}
	};
	EulerEngine::Application* EulerEngine::CreateApplication(ApplicationCommandLineArgs args) {
		ApplicationSpecification spec;
		spec.Name = "Euler Editor";
		spec.CmdArgs = args;
		return new EulerEditor(spec);
	}
}
