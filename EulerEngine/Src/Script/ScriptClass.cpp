#include"gkpch.h"
#include"ScriptClass.h"
#include"ScriptEngine.h"
namespace EulerEngine {
	ScriptClass::ScriptClass(const std::string& namespaceName, const std::string& className, bool isCore)
		: m_NamespaceName(namespaceName), m_ClassName(className)
	{
		if (isCore) {
			KINK_CORE_TRACE("Creating core class {0}::{1}", m_NamespaceName, m_ClassName);
			m_MonoClass = mono_class_from_name(ScriptEngine::GetData()->CoreImage, m_NamespaceName.c_str(), m_ClassName.c_str());
		}
		else {
			m_MonoClass = mono_class_from_name(ScriptEngine::GetData()->AppImage, m_NamespaceName.c_str(), m_ClassName.c_str());
		}
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