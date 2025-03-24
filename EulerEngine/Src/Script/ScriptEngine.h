#pragma once
#include<filesystem>
#include"mono/jit/jit.h"
#include"mono/metadata/assembly.h"
#include"mono/metadata/attrdefs.h"
#include"mono/metadata/mono-debug.h"
#include"mono/metadata/threads.h"
#include"ScriptClass.h"
#include"ScriptInstance.h"
#include"Core/Global/EulerUUID.h"
#include"World/EulerScene.h"
#include"World/EulerObject.h"
#include"filewatch/filewatch.h"
extern "C" {
	typedef struct _MonoAssembly MonoAssembly;
	typedef struct _MonoImage MonoImage;
	typedef struct _MonoClass MonoClass;
	typedef struct _MonoObject MonoObject;
	typedef struct _MonoMethod MonoMethod;
	typedef struct _MonoClassField MonoClassField;
}

namespace EulerEngine {
	using ScriptFieldMap = std::unordered_map<std::string, ScriptFieldInstance>;
	struct ScriptEngineData {
		MonoDomain* RootDomain = nullptr;
		MonoDomain* AppDomain = nullptr;

		MonoAssembly* CoreAssembly = nullptr;
		MonoImage* CoreImage = nullptr;

		MonoAssembly* AppAssembly = nullptr;
		MonoImage* AppImage = nullptr;

		ScriptClass SuperClass;
		std::unordered_map<std::string, Ref<ScriptClass>> GameObjectClasses;
		
		std::unordered_map<EulerUUID, Ref<ScriptInstance>> GameObjectInstances;
		std::unordered_map<EulerUUID, ScriptFieldMap> GameObjectScriptFields;

		std::filesystem::path CoreAssemblyPath;
		std::filesystem::path AppAssemblyPath;

		Scene* SceneContext = nullptr;

		Scope<filewatch::FileWatch<std::string>> AppAssemblyWatcher;
		bool AssemblyReloadPendding = false;
		bool EnableDebug = false;
	};
	class ScriptEngine {
	public:
		static void Init();
		static void ShutDown();
		static Ref<ScriptClass> GetGameObjectClass(std::string name);
		static std::unordered_map<std::string, Ref<ScriptClass>> GetGameObjectClasses();
		static ScriptFieldMap& GetScriptFieldMap(GameObject obj);
		static void OnRuntimeStart(Scene* scene);
		static void OnRuntimeStop();
		static bool IsClassExists(const std::string& fullName);
		static Scene* GetContext() { return GetData()->SceneContext; }
		static ScriptClass GetSuperClass() { return GetData()->SuperClass; }
		static MonoImage* GetCoreImage() { return GetData()->CoreImage; }

		static void OnCreateGameObject(GameObject obj);
		static void OnUpdateGameObject(GameObject obj);
		static void OnDestroyGameObject(GameObject obj);
		static Ref<ScriptInstance> GetScriptFromGameObject(EulerUUID uuid);
		static MonoObject* GetManagedInstance(uint64_t uuid);

		static void ReloadAssembly();
	private:
		static void InitMono();
		static void ShutDownMono();
		static MonoObject* InstantiateClass(MonoClass* monoClass);
		static void LoadAssembly(const std::filesystem::path& path);
		static void LoadAppAssembly(const std::filesystem::path& path);
		static void LoadAssemblyClasses();
		static ScriptEngineData* GetData();
		friend class ScriptClass;
	};
} 