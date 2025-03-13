#include"gkpch.h"
#include"ScriptEngine.h"
#include"mono/jit/jit.h"
#include"mono/metadata/assembly.h"
#include"GutKink/Core.h"
namespace EulerEngine {
	struct ScriptEngineData {
		MonoDomain* RootDomain = nullptr;
		MonoDomain* AppDomain = nullptr;

		MonoAssembly* CoreAssembly = nullptr;
	};
	static ScriptEngineData* s_Data;

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

	MonoAssembly* LoadCSharpAssembly(const std::string& filepath) {
		unsigned int file_size = 0;
		char* file_data = ReadBytes(filepath, &file_size);
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
		MonoAssembly* assembly = mono_assembly_load_from_full(image, filepath.c_str(), &status, false);
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
			KINK_CORE_INFO("Type: {0}.{1}", nameSpace, name);
		}
	}



	void ScriptEngine::Init()
	{
		s_Data = new ScriptEngineData();
		InitMono();
	}
	void ScriptEngine::ShutDown()
	{
		delete s_Data;
		s_Data = nullptr;
	}
	void ScriptEngine::InitMono()
	{
		mono_set_assemblies_path("Mono/lib");
		MonoDomain* root_domain = mono_jit_init("KinkJitRuntime");
		KINK_CORE_ASSERT(root_domain != nullptr, "Could not initialize mono runtime");
		s_Data->RootDomain = root_domain;
		s_Data->AppDomain = mono_domain_create_appdomain("KinkScriptRuntime", nullptr);
		mono_domain_set(s_Data->AppDomain, true);

		s_Data->CoreAssembly = LoadCSharpAssembly("Scripts/EulerScript.dll");
		PrintAssemblyTypes(s_Data->CoreAssembly);
	}
	void ScriptEngine::ShutDownMono()
	{
		mono_jit_cleanup(s_Data->RootDomain);
		mono_domain_unload(s_Data->AppDomain);
	}

}