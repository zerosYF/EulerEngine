#pragma once
#include<string>
#include"mono/jit/jit.h"
#include"mono/metadata/assembly.h"
namespace EulerEngine {
	class ScriptClass {
	public:
		ScriptClass() = default;
		ScriptClass(const std::string& namespaceName, const std::string& className, bool isCore = false);
		MonoObject* Instantiate();
		MonoMethod* GetMethod(const std::string& methodName, int paramCount);
		MonoObject* InvokeMethod(MonoObject* instance, MonoMethod* method, void** params);
		MonoClass* GetMonoClass() const { return m_MonoClass; }
	private:
		std::string m_NamespaceName;
		std::string m_ClassName;
		MonoClass* m_MonoClass;
	};
}