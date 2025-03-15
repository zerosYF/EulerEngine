#pragma once
#include<string>
#include"mono/jit/jit.h"
#include"mono/metadata/assembly.h"
#include"ScriptClass.h"
#include"GutKink/Core.h"
#include"World/EulerObject.h"
namespace EulerEngine {
	class ScriptInstance {
	public:
		ScriptInstance(Ref<ScriptClass> cls, GameObject obj);
		void InvokeOnCreate();
		void InvokeOnUpdate(float ts);
		void InvokeOnDestroy();
	private:
		Ref<ScriptClass> m_Cls;
		MonoObject* m_Instance;
		MonoMethod* m_Constructor;
		MonoMethod* m_OnCreate;
		MonoMethod* m_OnUpdate;
		MonoMethod* m_OnDestroy;
	};
}