using System;
using EulerEngine;
namespace Sandbox {
    public class Behaviour:Main {
        public float Speed = 5.0f;
        void OnCreate() { 
            Console.WriteLine("OnCreate called");
        }
        void OnUpdate(float ts) {
            Console.WriteLine("OnUpdate called with ts = " + ts);
        }
    }
}