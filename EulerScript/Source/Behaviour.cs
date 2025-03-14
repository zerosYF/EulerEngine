using System;
namespace Sandbox {
    public class Behaviour {
        void OnCreate() { 
            Console.WriteLine("OnCreate called");
        }
        void OnUpdate(float ts) {
            Console.WriteLine("OnUpdate called with ts = " + ts);
        }
    }
}