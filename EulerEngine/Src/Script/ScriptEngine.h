#pragma once
#include<filesystem>
#include"mono/jit/jit.h"
#include"mono/metadata/assembly.h"
#include"ScriptClass.h"
#include"GutKink/Core.h"
extern "C" {
	typedef struct _MonoAssembly MonoAssembly;
	typedef struct _MonoImage MonoImage;
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
		std::unordered_map<std::string, Ref<ScriptClass>> GameObjectClasses;
	};
	class ScriptEngine {
	public:
		static void Init();
		static void ShutDown();
		static void LoadAssembly(const std::filesystem::path& path);
		static std::unordered_map<std::string, Ref<ScriptClass>> GetGameObjectClasses();
	private:
		static void InitMono();
		static void ShutDownMono();
		static MonoObject* InstantiateClass(MonoClass* monoClass);
		static void LoadAssemblyClasses(MonoAssembly* assembly);
		static ScriptEngineData* GetData();
		friend class ScriptClass;
	};
} 