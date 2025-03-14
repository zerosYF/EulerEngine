#include"gkpch.h"
#include"ScriptInstance.h"
namespace EulerEngine {
	ScriptInstance::ScriptInstance(Ref<ScriptClass> cls): m_Cls(cls)
	{
		m_Instance = m_Cls->Instantiate();
		m_OnCreate = m_Cls->GetMethod("OnCreate", 0);
		m_OnUpdate = m_Cls->GetMethod("OnUpdate", 1);
	}
	void ScriptInstance::InvokeOnCreate()
	{
		m_Cls->InvokeMethod(m_Instance, m_OnCreate, nullptr);
	}
	void ScriptInstance::InvokeOnUpdate(float ts)
	{
		void* param = &ts;
		m_Cls->InvokeMethod(m_Instance, m_OnUpdate, &param);
	}
}