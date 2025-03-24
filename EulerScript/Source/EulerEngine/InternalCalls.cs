using System;
using System.Runtime.CompilerServices;

namespace EulerEngine {
    static class InternalCalls
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static float Transform_GetPosition(ulong uuid, out Vector3 pos);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static void Transform_SetPosition(ulong uuid, ref Vector3 pos);


        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static void Rigidbody2D_ApplyLinearImpulse(ulong uuid, ref Vector2 force);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static void Rigidbody2D_ApplyAngularImpulse(ulong uuid, ref float impulse);


        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static bool GameObject_HasComponent(ulong uuid, Type componentType);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static ulong GameObject_FindGameObjectByName(string name);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static object GameObject_GetScriptInstance(ulong uuid);

        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static float GetDeltaTime();
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static bool IsKeyDown(KeyCode key);
    }
}