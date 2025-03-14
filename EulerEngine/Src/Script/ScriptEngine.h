#pragma once
#include<filesystem>
#include"mono/jit/jit.h"
#include"mono/metadata/assembly.h"
#include"ScriptClass.h"
extern "C" {
	typedef struct _MonoClass MonoClass;
	typedef struct _MonoObject MonoObject;
	typedef struct _MonoMethod MonoMethod;
}

namespace EulerEngine {
	struct ScriptEngineData {
		MonoDomain* RootDomain = nullptr;
		MonoDomain* AppDomain = nullptr;

		MonoAssembly* CoreAssembly = nullptr;
		MonoImage* CoreImage = nullptr;
		ScriptClass GameObjectClass;
	};
	class ScriptEngine {
	public:
		static void Init();
		static void ShutDown();
		static void LoadAssembly(const std::filesystem::path& path);
	private:
		static void InitMono();
		static void ShutDownMono();
		static MonoObject* InstantiateClass(MonoClass* monoClass);
		static ScriptEngineData* GetData();
		friend class ScriptClass;
	};
} 