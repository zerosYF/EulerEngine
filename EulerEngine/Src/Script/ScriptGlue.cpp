#include"gkpch.h"
#include"ScriptGlue.h"
#include"ScriptEngine.h"
#include"mono/jit/jit.h"
#include"mono/metadata/assembly.h"
#include"mono/metadata/reflection.h"
#include"glm/glm.hpp"
#include"GutKink/Core.h"
#include"Core/IO/EulerInput.h"
#include"Core/Global/EulerTimer.h"
#define KINK_ADD_INTERNAL_CALL(Name) mono_add_internal_call("EulerEngine.InternalCalls::"#Name, Name) 
namespace EulerEngine {
    static std::unordered_map<MonoType*, std::function<bool(GameObject)>> s_HasComponentFuncs;

    static bool GameObject_HasComponent(uint64_t uuid, MonoReflectionType* componentName) {
        Scene* context = ScriptEngine::GetContext();
        GameObject obj = context->GetGameObject(uuid);

        MonoType* type = mono_reflection_type_get_type(componentName);
        return s_HasComponentFuncs[type](obj);
    }
    static uint64_t GameObject_FindGameObjectByName(MonoString* name) {
        char* cStr = mono_string_to_utf8(name);
        Scene* context = ScriptEngine::GetContext();
        GameObject obj = context->GetGameObjectByName(cStr);
        mono_free(cStr);
        if (!obj) {
            return 0;
        }
        return obj.GetUUID();
    }
    static MonoObject* GameObject_GetScriptInstance(uint64_t uuid) {
        return ScriptEngine::GetManagedInstance(uuid);     
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
    static void Rigidbody2D_ApplyLinearImpulse(uint64_t uuid, glm::vec2* force) {
        Scene* context = ScriptEngine::GetContext();
        GameObject obj = context->GetGameObject(uuid);
        b2BodyId body = obj.GetComponent<Rigidbody2D>().RuntimeBody;
        auto transform = obj.GetComponent<Transform>();
        b2Body_ApplyLinearImpulse(body, { force->x, force->y }, {transform.Position.x, transform.Position.y}, true);
    }
    static void Rigidbody2D_ApplyAngularImpulse(uint64_t uuid, float impulse) {
        Scene* context = ScriptEngine::GetContext();
        GameObject obj = context->GetGameObject(uuid);
        b2BodyId body = obj.GetComponent<Rigidbody2D>().RuntimeBody;
        b2Body_ApplyAngularImpulse(body, impulse, true);
    }
    static bool IsKeyDown(int key) {
        return InputSystem::IsKeyDown(key);
    }
    static float GetDeltaTime() {
        return TimerSystem::GetDeltaTime();
    }
    void ScriptGlue::RegisterFunctions()
    {
        KINK_CORE_TRACE("Registering internal calls");
        KINK_ADD_INTERNAL_CALL(GameObject_HasComponent);
        KINK_ADD_INTERNAL_CALL(GameObject_FindGameObjectByName);
        KINK_ADD_INTERNAL_CALL(GameObject_GetScriptInstance);
        KINK_ADD_INTERNAL_CALL(Transform_GetPosition);
        KINK_ADD_INTERNAL_CALL(Transform_SetPosition);
        KINK_ADD_INTERNAL_CALL(Rigidbody2D_ApplyLinearImpulse);
        KINK_ADD_INTERNAL_CALL(Rigidbody2D_ApplyAngularImpulse);
        KINK_ADD_INTERNAL_CALL(GetDeltaTime);
        KINK_ADD_INTERNAL_CALL(IsKeyDown);
    }
    template <typename ... Component>
    static void RegisterComponent() {
        ([]() {
            std::string name = typeid(Component).name();
            size_t pos = name.find_last_of(':');
            std::string struct_name = name.substr(pos + 1);
            std::string managed_name = fmt::format("EulerEngine.{}", struct_name);
            MonoType* type = mono_reflection_type_from_name(managed_name.data(), ScriptEngine::GetCoreImage());
            s_HasComponentFuncs[type] = [](GameObject obj) { return obj.HasComponent<Component>(); };
        }(), ...);
    }
    template <typename ... Component>
    static void RegisterComponent(ComponentGroup<Component...>) {
        RegisterComponent<Component...>();
    }
    void ScriptGlue::RegisterComponents()
    {
        s_HasComponentFuncs.clear();
        RegisterComponent(AllComponents{});
    }
}