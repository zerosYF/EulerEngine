#include"gkpch.h"
#include"ScriptClass.h"
#include"ScriptEngine.h"
namespace EulerEngine {
	ScriptClass::ScriptClass(const std::string& namespaceName, const std::string& className)
		: m_NamespaceName(namespaceName), m_ClassName(className)
	{
		m_MonoClass = mono_class_from_name(ScriptEngine::GetData()->CoreImage, m_NamespaceName.c_str(), m_ClassName.c_str());
	}
	MonoObject* ScriptClass::Instantiate()
	{
		return ScriptEngine::InstantiateClass(m_MonoClass);
	}
	MonoMethod* ScriptClass::GetMethod(const std::string& methodName, int paramCount)
	{
		return mono_class_get_method_from_name(m_MonoClass, methodName.c_str(), paramCount);
	}
	MonoObject* ScriptClass::InvokeMethod(MonoObject* instance, MonoMethod* method, void** params)
	{
		return mono_runtime_invoke(method, instance, params, nullptr);
	}
}