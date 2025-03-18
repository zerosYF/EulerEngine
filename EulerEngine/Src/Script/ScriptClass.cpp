#include"gkpch.h"
#include"ScriptClass.h"
#include"ScriptEngine.h"
namespace EulerEngine {
	static std::unordered_map<std::string, ScriptFieldType> s_ScriptFieldTypeMap = {
		{"System.Single", ScriptFieldType::Float},
		{"System.Double", ScriptFieldType::Double},
		{"System.String", ScriptFieldType::String},
		{"System.Boolean", ScriptFieldType::Bool},
		{"System.Char", ScriptFieldType::Char},
		{"System.Byte", ScriptFieldType::Byte},

		{"System.Int32", ScriptFieldType::Int},
		{"System.UInt32", ScriptFieldType::UInt},
		{"System.Int64", ScriptFieldType::Long},
		{"System.UInt64", ScriptFieldType::ULong},
		{"System.Int16", ScriptFieldType::Short},
		{"System.UInt16", ScriptFieldType::UShort},

		{"EulerEngine.Vector2", ScriptFieldType::Vector2},
		{"EulerEngine.Vector3", ScriptFieldType::Vector3},
		{"EulerEngine.Vector4", ScriptFieldType::Vector4},
		{"EulerEngine.GameObject", ScriptFieldType::GameObject},
	};

	ScriptFieldType ScriptClass::MonoTypeToScriptFieldType(MonoType* monoType)
	{
		std::string type_name = mono_type_get_name(monoType);
		if (s_ScriptFieldTypeMap.find(type_name) == s_ScriptFieldTypeMap.end()) {
			return ScriptFieldType::Unknown;
		}
		return s_ScriptFieldTypeMap[type_name];
	}

	std::string ScriptClass::FieldTypeToString(ScriptFieldType fieldType)
	{
		switch (fieldType) {
		case ScriptFieldType::Float: return "Float";
		case ScriptFieldType::Double: return "Double";
		case ScriptFieldType::Byte: return "Byte";
		case ScriptFieldType::Char: return "Char";
		case ScriptFieldType::String: return "String";
		case ScriptFieldType::Bool: return "Bool";
		case ScriptFieldType::Int: return "Int";
		case ScriptFieldType::UInt: return "UInt";
		case ScriptFieldType::Short: return "Short";
		case ScriptFieldType::UShort: return "UShort";
		case ScriptFieldType::Long: return "Long";
		case ScriptFieldType::ULong: return "ULong";
		case ScriptFieldType::Vector2: return "Vector2";
		case ScriptFieldType::Vector3: return "Vector3";
		case ScriptFieldType::Vector4: return "Vector4";
		case ScriptFieldType::GameObject: return "GameObject";
		default: return "Unknown";
		}
	}

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