#pragma once
#include<string>
#include"mono/jit/jit.h"
#include"mono/metadata/assembly.h"
namespace EulerEngine {
	enum class ScriptFieldType {
		Unknown = 0, 
		Char, Bool, Double, Byte, String,
		Float, Vector2, Vector3, Vector4,
		Int, UInt, Short, UShort,
		Long, ULong, GameObject,
	};
	struct ScriptField {
		std::string Name;
		ScriptFieldType Type;
		MonoClassField* ClassField;
	};
	class ScriptClass {
	public:
		ScriptClass() = default;
		ScriptClass(const std::string& namespaceName, const std::string& className, bool isCore = false);
		MonoObject* Instantiate();
		MonoMethod* GetMethod(const std::string& methodName, int paramCount);
		MonoObject* InvokeMethod(MonoObject* instance, MonoMethod* method, void** params);
		MonoClass* GetMonoClass() const { return m_MonoClass; }
		static ScriptFieldType MonoTypeToScriptFieldType(MonoType* monoType);
		static std::string FieldTypeToString(ScriptFieldType fieldType);
		const std::map<std::string, ScriptField>& GetFields() const { return m_Fields; }
	private:
		std::string m_NamespaceName;
		std::string m_ClassName;
		MonoClass* m_MonoClass;
		std::map<std::string, ScriptField> m_Fields;
		friend class ScriptEngine;
	};
}