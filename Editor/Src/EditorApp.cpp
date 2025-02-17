#include<GutKink.h>
#include<GutKink/EntryPoint.h>
#include"EditorLayer.h"
namespace EulerEngine {
	class EulerEditor : public EulerEngine::Application {
	public:
		EulerEditor() {
			PushLayer(new EditorLayer());
		}
		~EulerEditor() {
		}
	};
	EulerEngine::Application* EulerEngine::CreateApplication() {
		return new EulerEditor();
	}
}
