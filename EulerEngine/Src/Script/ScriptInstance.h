#pragma once
#include<string>
#include"mono/jit/jit.h"
#include"mono/metadata/assembly.h"
#include"ScriptClass.h"
#include"GutKink/Core.h"
namespace EulerEngine {
	class ScriptInstance {
	public:
		ScriptInstance(Ref<ScriptClass> cls);
		void InvokeOnCreate();
		void InvokeOnUpdate(float ts);
		void InvokeOnDestroy();
	private:
		Ref<ScriptClass> m_Cls;
		MonoObject* m_Instance;
		MonoMethod* m_OnCreate;
		MonoMethod* m_OnUpdate;
		MonoMethod* m_OnDestroy;
	};
}