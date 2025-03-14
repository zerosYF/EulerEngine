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
    public class Main {
        public float FloatVar { get; set; }
        public Main() { 
            Console.WriteLine("Initializing Main class");
            Vector3 vec3 = new Vector3(1.0f, 2.0f, 3.0f);
            Vector3 result = Log(vec3);
            Console.WriteLine("Result: " + result.x + " " + result.y + " " + result.z);
            Console.WriteLine("Dot product: " + InternalCalls.NativeLog_Vec3Dot(ref vec3));
        }
        public void PrintMsg() { 
            Console.WriteLine("Hello from C#");
        }
        public void PrintInt(int value) { 
            Console.WriteLine("Hello from C# with int value: " + value);
        }
        public void PrintInt_2(int value1, int value2) {
            Console.WriteLine("Hello from C# with int values: " + value1 + " and " + value2);
        }
        public void PrintString(string text) {
            Console.WriteLine("Hello from C# with string: " + text);
        }
        private void Log(string text, int param) {
            InternalCalls.NativeLog(text, param);
        }
        private Vector3 Log(Vector3 param) {
            InternalCalls.NativeLog_Vec3(ref param, out Vector3 result);
            return result;
        }
    };
}