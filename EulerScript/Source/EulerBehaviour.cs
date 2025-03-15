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
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void NativeLog(string text, int param);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static void NativeLog_Vec3(ref Vector3 param, out Vector3 result);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        internal extern static float NativeLog_Vec3Dot(ref Vector3 param);
    }
    public class EulerBehaviour
    {
        public EulerBehaviour() { 
            Console.WriteLine("Initializing EulerBehaviour class");
        }
    };
}