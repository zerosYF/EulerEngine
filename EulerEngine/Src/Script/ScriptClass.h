#pragma once
#include<string>
#include"mono/jit/jit.h"
#include"mono/metadata/assembly.h"
namespace EulerEngine {
	enum class ScriptFieldType {
		Unknown = 0, 
		Char, Bool, Double, String,
		Float, Vector2, Vector3, Vector4,
		Int, UInt, Short, UShort,
		Long, ULong, Byte, UByte,GameObject,
	};
	struct ScriptField {
		std::string Name;
		ScriptFieldType Type;
		MonoClassField* ClassField;
	};
	struct ScriptFieldInstance {
	public:
		ScriptField Field;
		ScriptFieldInstance() {
			memset(Data, 0, sizeof(Data));
		}
		template<typename T>
		T& GetData() {
			return *(T*)Data;
		}
		template<typename T>
		void SetData(T value) {
			if (constexpr(sizeof(T) <= 16)) {
				memcpy(Data, &value, sizeof(T));
			}
		}
		const char* GetRawData() const { return Data; }
	private:
		char Data[16];
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
		static std::string ScriptFieldTypeToString(ScriptFieldType fieldType);
		static ScriptFieldType StringToScriptFieldType(const std::string& fieldType);
		const std::map<std::string, ScriptField>& GetFields() const { return m_Fields; }
	private:
		std::string m_NamespaceName;
		std::string m_ClassName;
		MonoClass* m_MonoClass;
		std::map<std::string, ScriptField> m_Fields;
		friend class ScriptEngine;
	};
}