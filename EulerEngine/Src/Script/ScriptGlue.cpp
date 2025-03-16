#include"gkpch.h"
#include"ScriptGlue.h"
#include"ScriptEngine.h"
#include"mono/jit/jit.h"
#include"mono/metadata/assembly.h"
#include"mono/metadata/reflection.h"
#include"glm/glm.hpp"
#include"GutKink/Core.h"
#include"Core/Input/EulerInput.h"
#define KINK_ADD_INTERNAL_CALL(Name) mono_add_internal_call("EulerEngine.InternalCalls::"#Name, Name) 
namespace EulerEngine {
    static std::unordered_map<MonoType*, std::function<bool(GameObject)>> s_HasComponentFuncs;

    static bool GameObject_HasComponent(uint64_t uuid, MonoReflectionType* componentName) {
        Scene* context = ScriptEngine::GetContext();
        GameObject obj = context->GetGameObject(uuid);

        MonoType* type = mono_reflection_type_get_type(componentName);
        return s_HasComponentFuncs[type](obj);
    }
    static void Transform_GetPosition(uint64_t uuid, glm::vec3* position) {
        Scene* context = ScriptEngine::GetContext();
        GameObject obj = context->GetGameObject(uuid);
        *position = obj.GetComponent<Transform>().Position;
    }
    static void Transform_SetPosition(uint64_t uuid, glm::vec3* position) {
        Scene* context = ScriptEngine::GetContext();
        GameObject obj = context->GetGameObject(uuid);
        obj.GetComponent<Transform>().Position = *position;
    }
    static bool IsKeyDown(int key) {
        return InputSystem::IsKeyDown(key);
    }
    void ScriptGlue::RegisterFunctions()
    {
        KINK_CORE_TRACE("Registering internal calls");
        KINK_ADD_INTERNAL_CALL(GameObject_HasComponent);
        KINK_ADD_INTERNAL_CALL(Transform_GetPosition);
        KINK_ADD_INTERNAL_CALL(Transform_SetPosition);
        KINK_ADD_INTERNAL_CALL(IsKeyDown);
    }
    template <typename Component>
    static void RegisterComponent() {
        std::string name = typeid(Component).name();
        size_t pos = name.find_last_of(':');
        std::string struct_name = name.substr(pos + 1);
        std::string managed_name = fmt::format("EulerEngine.{}", struct_name);
        MonoType* type = mono_reflection_type_from_name(managed_name.data(), ScriptEngine::GetCoreImage());
        s_HasComponentFuncs[type] = [](GameObject obj) { return obj.HasComponent<Component>(); };
    }
    void ScriptGlue::RegisterComponents()
    {
        RegisterComponent<Transform>();
    }
}