#include"gkpch.h"
#include"ScriptGlue.h"
#include"ScriptEngine.h"
#include"GutKink/Core.h"
#include"GutKink/Application.h"
#include"Core/Memory/EulerBuffer.h"
#include"Core/IO/FileSystem.h"
namespace EulerEngine {
	extern ScriptEngineData* s_Data = nullptr;

	MonoAssembly* LoadMonoAssembly(const std::filesystem::path& filepath, bool load_pdb = false) {
		ScopedBuffer file_data = FileSystem::ReadFileBinary(filepath.string());
		MonoImageOpenStatus status;
		MonoImage* image = mono_image_open_from_data_full(file_data.As<char>(), file_data.Size(), true, &status, false);
		if (status != MONO_IMAGE_OK) {
			KINK_CORE_ERROR("Could not load assembly: {0}", mono_image_strerror(status));
			return nullptr;
		}
		MonoAssembly* assembly = mono_assembly_load_from_full(image, filepath.string().c_str(), &status, false);
		if (assembly == nullptr) {
			return nullptr;
		}
		mono_image_close(image);
		if (load_pdb) {
			std::filesystem::path pdb_path = filepath;
			pdb_path.replace_extension(".pdb");
			KINK_CORE_INFO("Loading PDB: {0}", pdb_path.string());
			if (std::filesystem::exists(pdb_path)) {
				ScopedBuffer pdb_data = FileSystem::ReadFileBinary(pdb_path.string());
				mono_debug_open_image_from_memory(image, pdb_data.As<const mono_byte>(), pdb_data.Size());
			}
		}
		return assembly;
	}
	
	void ScriptEngine::LoadAssembly(const std::filesystem::path& path)
	{
		KINK_CORE_TRACE("Loading assembly: {0}", path.string());
		s_Data->AppDomain = mono_domain_create_appdomain("KinkScriptRuntime", nullptr);
		mono_domain_set(s_Data->AppDomain, true);
		s_Data->CoreAssemblyPath = path;
		s_Data->CoreAssembly = LoadMonoAssembly(path, s_Data->EnableDebug);
		s_Data->CoreImage = mono_assembly_get_image(s_Data->CoreAssembly);
	}

	static void OnAppAssemblyFileSystemEvent(const std::string& path, const filewatch::Event change_type) {
		if (!s_Data->AssemblyReloadPendding && change_type == filewatch::Event::modified) {
			s_Data->AssemblyReloadPendding = true;
			Application::Get().SubmitToMainThread([](){
				s_Data->AppAssemblyWatcher.reset();
				ScriptEngine::ReloadAssembly(); 
			});
		}
	}

	void ScriptEngine::LoadAppAssembly(const std::filesystem::path& path)
	{
		KINK_CORE_TRACE("Loading app assembly: {0}", path.string());
		s_Data->AppAssemblyPath = path;
		s_Data->AppAssembly = LoadMonoAssembly(path, s_Data->EnableDebug);
		s_Data->AppImage = mono_assembly_get_image(s_Data->AppAssembly);

		s_Data->AppAssemblyWatcher = CreateScope<filewatch::FileWatch<std::string>>(path.string(), OnAppAssemblyFileSystemEvent);
		s_Data->AssemblyReloadPendding = false;
	}

	void ScriptEngine::LoadAssemblyClasses() {
		KINK_CORE_TRACE("Loading assembly classes");
		s_Data->GameObjectClasses.clear();
		const MonoTableInfo* typeDefinationTable = mono_image_get_table_info(s_Data->AppImage, MONO_TABLE_TYPEDEF);
		unsigned int num_types = mono_table_info_get_rows(typeDefinationTable);

		MonoClass* super_cls = s_Data->SuperClass.GetMonoClass();
		for (unsigned int i = 0; i < num_types; i++) {
			unsigned int cols[MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(typeDefinationTable, i, cols, MONO_TYPEDEF_SIZE);
			const char* name_space = mono_metadata_string_heap(s_Data->AppImage, cols[MONO_TYPEDEF_NAMESPACE]);
			const char* class_name = mono_metadata_string_heap(s_Data->AppImage, cols[MONO_TYPEDEF_NAME]);
			std::string final_name = std::string(class_name);
			if (strlen(name_space) != 0) {
				final_name = std::string(name_space) + "." + std::string(class_name);
			}
			MonoClass* cls = mono_class_from_name(s_Data->AppImage, name_space, class_name);
			if (cls == super_cls) {
				continue;
			}
			bool isSubCls = mono_class_is_subclass_of(cls, super_cls, false);
			if (isSubCls) {
				Ref<ScriptClass> script_cls = CreateRef<ScriptClass>(name_space, class_name);

				s_Data->GameObjectClasses[final_name] = script_cls;
				int cnt = mono_class_num_fields(cls);
				void* iter = nullptr;
				while (MonoClassField* field = mono_class_get_fields(cls, &iter)){
					const char* field_name = mono_field_get_name(field);
					unsigned int flags = mono_field_get_flags(field);
					if (flags & MONO_FIELD_ATTR_PUBLIC) {
						MonoType* type = mono_field_get_type(field);
						ScriptFieldType field_type = ScriptClass::MonoTypeToScriptFieldType(type);
						script_cls->m_Fields[field_name] = { field_name, field_type, field };
					}
				}
			}
		}
	}

	void ScriptEngine::Init()
	{
		s_Data = new ScriptEngineData();
		InitMono();
		ScriptGlue::RegisterFunctions();
		LoadAssembly("Scripts/EulerScript.dll");
		LoadAppAssembly("Project/Assets/Scripts/Binaries/Sandbox.dll");
		s_Data->SuperClass = ScriptClass("EulerEngine", "EulerBehaviour", true);
		LoadAssemblyClasses();
		ScriptGlue::RegisterComponents();

	}
	void ScriptEngine::ShutDown()
	{
		ShutDownMono();
		delete s_Data;
		s_Data = nullptr;
	}
	Ref<ScriptClass> ScriptEngine::GetGameObjectClass(std::string name)
	{
		if (s_Data->GameObjectClasses.find(name) != s_Data->GameObjectClasses.end()) {
			return s_Data->GameObjectClasses[name];
		}
		return nullptr;
	}
	std::unordered_map<std::string, Ref<ScriptClass>> ScriptEngine::GetGameObjectClasses()
	{
		return s_Data->GameObjectClasses;
	}
	ScriptFieldMap& ScriptEngine::GetScriptFieldMap(GameObject obj)
	{
		return s_Data->GameObjectScriptFields[obj.GetUUID()];
	}
	void ScriptEngine::OnRuntimeStart(Scene* scene)
	{
		s_Data->SceneContext = scene;
	}
	void ScriptEngine::OnRuntimeStop()
	{
		s_Data->SceneContext = nullptr;
	}
	bool ScriptEngine::IsClassExists(const std::string& fullName)
	{
		return s_Data->GameObjectClasses.find(fullName) != s_Data->GameObjectClasses.end();
	}
	void ScriptEngine::OnCreateGameObject(GameObject obj)
	{
		const auto& com = obj.GetComponent<CSharpScript>();
		if (IsClassExists(com.Name)) {
			EulerUUID uuid = obj.GetUUID();
			Ref<ScriptInstance> instance = CreateRef<ScriptInstance>(s_Data->GameObjectClasses[com.Name], obj);
			s_Data->GameObjectInstances[uuid] = instance;
			if (s_Data->GameObjectScriptFields.find(uuid) != s_Data->GameObjectScriptFields.end()) {
				const ScriptFieldMap& map = s_Data->GameObjectScriptFields[uuid];
				for (const auto& [name, field_instance] : map) {
					instance->SetRawFieldValue(name, field_instance.GetRawData());
				}
			}
			instance->InvokeOnCreate();
		}
	}
	void ScriptEngine::OnUpdateGameObject(GameObject obj)
	{
		KINK_CORE_ASSERT(s_Data->GameObjectInstances.find(obj.GetUUID()) != s_Data->GameObjectInstances.end(), "GameObject instance not found");
		Ref<ScriptInstance> instance = s_Data->GameObjectInstances[obj.GetUUID()];
		instance->InvokeOnUpdate();
	}
	void ScriptEngine::OnDestroyGameObject(GameObject obj)
	{
		KINK_CORE_ASSERT(s_Data->GameObjectInstances.find(obj.GetUUID()) != s_Data->GameObjectInstances.end(), "GameObject instance not found");
		Ref<ScriptInstance> instance = s_Data->GameObjectInstances[obj.GetUUID()];
		instance->InvokeOnDestroy();
	}
	Ref<ScriptInstance> ScriptEngine::GetScriptFromGameObject(EulerUUID uuid)
	{
		auto iter = s_Data->GameObjectInstances.find(uuid);
		if (iter != s_Data->GameObjectInstances.end()) {
			return iter->second;
		}
		return nullptr;
	}
	MonoObject* ScriptEngine::GetManagedInstance(uint64_t uuid)
	{
		if (s_Data->GameObjectInstances.find(uuid) != s_Data->GameObjectInstances.end()) {
			Ref<ScriptInstance> instance = s_Data->GameObjectInstances[uuid];
			return instance->GetMonoObject();
		}
		return nullptr;
	}
	void ScriptEngine::ReloadAssembly()
	{
		mono_domain_set(mono_get_root_domain(), false);
		mono_domain_unload(s_Data->AppDomain);

		LoadAssembly(s_Data->CoreAssemblyPath);
		LoadAppAssembly(s_Data->AppAssemblyPath);
		s_Data->SuperClass = ScriptClass("EulerEngine", "EulerBehaviour", true);
		LoadAssemblyClasses();
		ScriptGlue::RegisterComponents();
	}
	MonoObject* ScriptEngine::InstantiateClass(MonoClass* monoClass)
	{
		MonoObject* obj = mono_object_new(s_Data->AppDomain, monoClass);
		mono_runtime_object_init(obj);
		return obj;
	}
	ScriptEngineData* ScriptEngine::GetData()
	{
		return s_Data;
	}
	void ScriptEngine::InitMono()
	{
		mono_set_assemblies_path("Mono/lib");
		if (s_Data->EnableDebug) {
			const char* argv[2] = {
				"--debugger-agent=transport=dt_socket,server=y,suspend=n,address=127.0.0.1:2550,loglevel=3,logfile= KinkDebug.log",
				"--soft-breakpoints"
			};
			mono_jit_parse_options(2, (char**)argv);
			mono_debug_init(MONO_DEBUG_FORMAT_MONO);
		}
		MonoDomain* root_domain = mono_jit_init("KinkJitRuntime");
		KINK_CORE_ASSERT(root_domain != nullptr, "Could not initialize mono runtime");
		s_Data->RootDomain = root_domain;
		if (s_Data->EnableDebug) {
			mono_debug_domain_create(s_Data->RootDomain);
		}
		mono_thread_set_main(mono_thread_current());
	}
	void ScriptEngine::ShutDownMono()
	{
		mono_domain_set(mono_get_root_domain(), false);
		mono_domain_unload(s_Data->AppDomain);
		s_Data->AppDomain = nullptr;
		mono_jit_cleanup(s_Data->RootDomain);
		s_Data->RootDomain = nullptr;
	}

}