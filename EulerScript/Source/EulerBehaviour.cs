using System;
using System.Runtime.CompilerServices;
namespace EulerEngine {
    public struct Vector3
    {
        public float x;
        public float y;
        public float z;
        public Vector3(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }
    }
    static class InternalCalls
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static void NativeLog(string text, int param);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static void NativeLog_Vec3(ref Vector3 param, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static float NativeLog_Vec3Dot(ref Vector3 param);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static float GetPosition(ulong uuid, out Vector3 pos);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static void SetPosition(ulong uuid, ref Vector3 pos);
        [MethodImpl(MethodImplOptions.InternalCall)]
        internal extern static bool IsKeyDown(KeyCode key);
    }
    public class EulerBehaviour
    {
        protected EulerBehaviour() {
            this.uuid = 0;
        }
        internal EulerBehaviour(ulong uuid) {
            this.uuid = uuid;
        }
        public readonly ulong uuid;
        public Vector3 position
        {
            get {
                InternalCalls.GetPosition(uuid, out Vector3 pos);
                return pos;
            }
            set {
                InternalCalls.SetPosition(uuid, ref value);
            }
        }
    };
}