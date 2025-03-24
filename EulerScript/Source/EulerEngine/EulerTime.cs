using System;
namespace EulerEngine {
    public class EulerTime
    {
        public static float GetDeltaTime() {
            return InternalCalls.GetDeltaTime();
        }
    }
}