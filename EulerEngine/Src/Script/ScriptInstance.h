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
		Ref<ScriptClass> GetClass() { return m_Cls; }
		template<typename T>
		T GetFieldValue(const std::string& fieldName) {
			const auto& fields = m_Cls->GetFields();
			if (fields.find(fieldName) == fields.end()) {
				return T();
			}
			static char buffer[8];
			ScriptField field = fields.at(fieldName);
			mono_field_get_value(m_Instance, field.ClassField, buffer);
			return *(T*)buffer;
		}
		template<typename T>
		void SetFieldValue(const std::string& fieldName, T value) {
			const auto& fields = m_Cls->GetFields();
			if (fields.find(fieldName) == fields.end()) {
				return;
			}
			ScriptField field = fields.at(fieldName);
			mono_field_set_value(m_Instance, field.ClassField, &value);
		}
	private:
		Ref<ScriptClass> m_Cls;
		MonoObject* m_Instance;
		MonoMethod* m_Constructor;
		MonoMethod* m_OnCreate;
		MonoMethod* m_OnUpdate;
		MonoMethod* m_OnDestroy;
	};
}