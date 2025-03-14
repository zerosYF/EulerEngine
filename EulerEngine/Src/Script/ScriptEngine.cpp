#include"gkpch.h"
#include"ScriptGlue.h"
#include"ScriptEngine.h"
#include"GutKink/Core.h"
namespace EulerEngine {
	extern ScriptEngineData* s_Data = nullptr;
	// TODO:be a filesystem method
	char* ReadBytes(const std::string& filepath, unsigned int* out_size) {
		std::ifstream stream(filepath, std::ios::binary | std::ios::ate);
		if (!stream) {
			return nullptr;
		}
		std::streampos end = stream.tellg();
		stream.seekg(0, std::ios::beg);
		unsigned int size = end - stream.tellg();
		if (size == 0) {
			return nullptr;
		}
		char* buffer = new char[size];
		stream.read((char*)buffer, size);
		*out_size = size;
		return buffer;
	}

	MonoAssembly* LoadMonoAssembly(const std::filesystem::path& filepath) {
		unsigned int file_size = 0;
		char* file_data = ReadBytes(filepath.string(), &file_size);
		if (file_data == nullptr) {
			return nullptr;
		}
		MonoImageOpenStatus status;
		MonoImage* image = mono_image_open_from_data_full(file_data, file_size, true, &status, false);
		delete[] file_data;
		if (status != MONO_IMAGE_OK) {
			KINK_CORE_ERROR("Could not load assembly: {0}", mono_image_strerror(status));
			return nullptr;
		}
		MonoAssembly* assembly = mono_assembly_load_from_full(image, filepath.string().c_str(), &status, false);
		if (assembly == nullptr) {
			return nullptr;
		}
		mono_image_close(image);
		return assembly;
	}

	void PrintAssemblyTypes(MonoAssembly* assembly) {
		MonoImage* image = mono_assembly_get_image(assembly);
		const MonoTableInfo* typeDefinationTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
		unsigned int num_types = mono_table_info_get_rows(typeDefinationTable);
		for (unsigned int i = 0; i < num_types; i++) {
			unsigned int cols[MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(typeDefinationTable, i, cols, MONO_TYPEDEF_SIZE);
			const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
			const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);
			MonoClass* cls = mono_class_from_name(image, nameSpace, name);
			MonoClass* obj_cls = mono_class_from_name(image, "EulerEngine", "Main");
			bool isSubCls = mono_class_is_subclass_of(cls, obj_cls, false);
			KINK_CORE_TRACE("Type: {0}.{1}", nameSpace, name);
		}
	}

	void ScriptEngine::LoadAssemblyClasses(MonoAssembly* assembly) {
		s_Data->GameObjectClasses.clear();

		MonoImage* image = mono_assembly_get_image(assembly);
		const MonoTableInfo* typeDefinationTable = mono_image_get_table_info(image, MONO_TABLE_TYPEDEF);
		unsigned int num_types = mono_table_info_get_rows(typeDefinationTable);

		MonoClass* super_cls = mono_class_from_name(image, "EulerEngine", "Main");
		for (unsigned int i = 0; i < num_types; i++) {
			unsigned int cols[MONO_TYPEDEF_SIZE];
			mono_metadata_decode_row(typeDefinationTable, i, cols, MONO_TYPEDEF_SIZE);
			const char* nameSpace = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAMESPACE]);
			const char* name = mono_metadata_string_heap(image, cols[MONO_TYPEDEF_NAME]);
			std::string final_name = std::string(name);
			if (strlen(nameSpace) != 0) {
				final_name = std::string(nameSpace) + "." + std::string(name);
			}
			MonoClass* cls = mono_class_from_name(image, nameSpace, name);
			if (cls == super_cls) {
				continue;
			}
			bool isSubCls = mono_class_is_subclass_of(cls, super_cls, false);
			if (isSubCls) {
				s_Data->GameObjectClasses[final_name] = CreateRef<ScriptClass>(nameSpace, name);
			}
		}
	}

	void ScriptEngine::Init()
	{
		s_Data = new ScriptEngineData();
		InitMono();
		LoadAssembly("Scripts/EulerScript.dll");
		LoadAssemblyClasses(s_Data->CoreAssembly);
		ScriptGlue::RegisterFunctions();
		PrintAssemblyTypes(s_Data->CoreAssembly);
	}
	void ScriptEngine::ShutDown()
	{
		ShutDownMono();
		delete s_Data;
		s_Data = nullptr;
	}
	void ScriptEngine::LoadAssembly(const std::filesystem::path& path)
	{
		s_Data->AppDomain = mono_domain_create_appdomain("KinkScriptRuntime", nullptr);
		mono_domain_set(s_Data->AppDomain, true);
		s_Data->CoreAssembly = LoadMonoAssembly(path);
		s_Data->CoreImage = mono_assembly_get_image(s_Data->CoreAssembly);
	}
	std::unordered_map<std::string, Ref<ScriptClass>> ScriptEngine::GetGameObjectClasses()
	{
		return s_Data->GameObjectClasses;
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
		MonoDomain* root_domain = mono_jit_init("KinkJitRuntime");
		KINK_CORE_ASSERT(root_domain != nullptr, "Could not initialize mono runtime");
		s_Data->RootDomain = root_domain;
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