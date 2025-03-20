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
		if (m_OnCreate == nullptr) {
			return;
		}
		m_Cls->InvokeMethod(m_Instance, m_OnCreate, nullptr);
	}
	void ScriptInstance::InvokeOnUpdate(float ts)
	{
		if (m_OnUpdate == nullptr) {
			return;
		}
		void* param = &ts;
		m_Cls->InvokeMethod(m_Instance, m_OnUpdate, &param);
	}
	void ScriptInstance::InvokeOnDestroy()
	{
		if (m_OnDestroy == nullptr) {
			return;
		}
		m_Cls->InvokeMethod(m_Instance, m_OnDestroy, nullptr);
	}
	bool ScriptInstance::GetRawFieldValue(const std::string& fieldName, void* buffer)
	{
		const auto& fields = m_Cls->GetFields();
		auto it = fields.find(fieldName);
		if (it == fields.end()) {
			return false;
		}
		const ScriptField& field = it->second;
		mono_field_get_value(m_Instance, field.ClassField, buffer);
		return true;
	}
	bool ScriptInstance::SetRawFieldValue(const std::string& fieldName, const void* buffer)
	{
		const auto& fields = m_Cls->GetFields();
		auto it = fields.find(fieldName);
		if (it == fields.end()) {
			return false;
		}
		const ScriptField& field = it->second;
		mono_field_set_value(m_Instance, field.ClassField, (void*)buffer);
		return true;
	}
}