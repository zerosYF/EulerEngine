#include"gkpch.h"
#include"ScriptGlue.h"
#include"mono/jit/jit.h"
#include"mono/metadata/assembly.h"
#include"glm/glm.hpp"
#define KINK_ADD_INTERNAL_CALL(Name) mono_add_internal_call("EulerEngine.InternalCalls::"#Name, Name) 
namespace EulerEngine {
    static void NativeLog(MonoString* text, int param) {
        char* cStr = mono_string_to_utf8(text);
        std::string str(cStr);
        mono_free(cStr);
        std::cout << str << ":" << param << std::endl;
    }
    static void NativeLog_Vec3(glm::vec3* param, glm::vec3* result) {
        *result = glm::normalize(*param);
    }
    static float NativeLog_Vec3Dot(glm::vec3* param) {
        return glm::dot(*param, *param);
    }
    void ScriptGlue::RegisterFunctions()
    {
        KINK_ADD_INTERNAL_CALL(NativeLog);
        KINK_ADD_INTERNAL_CALL(NativeLog_Vec3);
        KINK_ADD_INTERNAL_CALL(NativeLog_Vec3Dot);
    }
}