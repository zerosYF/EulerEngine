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
		void InvokeOnUpdate();
		void InvokeOnDestroy();
		Ref<ScriptClass> GetClass() { return m_Cls; }
		template<typename T>
		T GetFieldValue(const std::string& fieldName) {
			char buffer[16];
			bool suc = GetRawFieldValue(fieldName, &buffer);
			if (!suc) {
				return T();
			}
			return *(T*)buffer;
		}
		template<typename T>
		void SetFieldValue(const std::string& fieldName, T value) {
			SetRawFieldValue(fieldName, &value);
		}
		bool GetRawFieldValue(const std::string& fieldName, void* buffer);
		bool SetRawFieldValue(const std::string& fieldName, const void* buffer);

		MonoObject* GetMonoObject() { return m_Instance; }
	private:
		Ref<ScriptClass> m_Cls;
		MonoObject* m_Instance;
		MonoMethod* m_Constructor;
		MonoMethod* m_OnCreate;
		MonoMethod* m_OnUpdate;
		MonoMethod* m_OnDestroy;
	};
}