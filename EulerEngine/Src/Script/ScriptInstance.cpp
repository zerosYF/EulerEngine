#include"gkpch.h"
#include"ScriptInstance.h"
#include"ScriptEngine.h"
namespace EulerEngine {
	ScriptInstance::ScriptInstance(Ref<ScriptClass> cls, GameObject obj): m_Cls(cls)
	{
		m_Instance = m_Cls->Instantiate();
		m_Constructor = ScriptEngine::GetSuperClass().GetMethod(".ctor", 1);
		m_OnCreate = m_Cls->GetMethod("OnCreate", 0);
		m_OnUpdate = m_Cls->GetMethod("OnUpdate", 1);
		m_OnDestroy = m_Cls->GetMethod("OnDestroy", 0);
		{
			uint64_t uuid = obj.GetUUID();
			void* param = &uuid;
			m_Cls->InvokeMethod(m_Instance, m_Constructor, &param);
		}
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
	void ScriptInstance::InvokeOnDestroy()
	{
		m_Cls->InvokeMethod(m_Instance, m_OnDestroy, nullptr);
	}
}