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
        internal extern static bool GameObject_HasComponent(ulong uuid, Type componentType);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static bool IsKeyDown(KeyCode key);
    }
}