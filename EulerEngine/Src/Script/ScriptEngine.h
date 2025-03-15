#pragma once
#include<filesystem>
#include"mono/jit/jit.h"
#include"mono/metadata/assembly.h"
#include"ScriptClass.h"
#include"ScriptInstance.h"
#include"GutKink/Core.h"
#include"World/EulerScene.h"
#include"World/EulerObject.h"
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
		ScriptClass SuperClass;
		std::unordered_map<std::string, Ref<ScriptClass>> GameObjectClasses;
		std::unordered_map<EulerUUID, Ref<ScriptInstance>> GameObjectInstances;

		Scene* SceneContext;
	};
	class ScriptEngine {
	public:
		static void Init();
		static void ShutDown();
		static std::unordered_map<std::string, Ref<ScriptClass>> GetGameObjectClasses();
		static void OnRuntimeStart(Scene* scene);
		static void OnRuntimeStop();
		static bool IsClassExists(const std::string& fullName);
		static Scene* GetContext() { return GetData()->SceneContext; }
		static ScriptClass GetSuperClass() { return GetData()->SuperClass; }

		static void OnCreateGameObject(GameObject obj);
		static void OnUpdateGameObject(GameObject obj, float ts);
		static void OnDestroyGameObject(GameObject obj);
	private:
		static void InitMono();
		static void ShutDownMono();
		static MonoObject* InstantiateClass(MonoClass* monoClass);
		static void LoadAssembly(const std::filesystem::path& path);
		static void LoadAssemblyClasses(MonoAssembly* assembly);
		static ScriptEngineData* GetData();
		friend class ScriptClass;
	};
} 