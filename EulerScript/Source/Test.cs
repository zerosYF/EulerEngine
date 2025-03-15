using System;
using EulerEngine;
namespace Sandbox {
    public class Test:EulerBehaviour {
        void OnCreate() { 
            Console.WriteLine("OnCreate called");
        }
        void OnUpdate(float ts) {
            Console.WriteLine("OnUpdate called with ts = " + ts);
        }
        void OnDestroy() { 
            Console.WriteLine("OnDestroy called");
        }
    }
}