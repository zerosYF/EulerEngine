using System.Runtime.CompilerServices;

namespace EulerEngine {
    public class Input {
        public static bool IsKeyDown(KeyCode key) { 
            return InternalCalls.IsKeyDown(key);
        }
    }
}