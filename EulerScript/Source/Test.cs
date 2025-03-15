using System;
using EulerEngine;
namespace Sandbox {
    public class Test:EulerBehaviour {
        void OnCreate() { 
            Console.WriteLine("OnCreate called:" + this.uuid);
        }
        void OnUpdate(float ts) {
            Console.WriteLine("OnUpdate called with ts = " + ts);
            float speed = 1.0f;
            Vector3 pos = position;
            pos.x += speed * ts;
            if (Input.IsKeyDown(KeyCode.KINK_KEY_W))
            {
                pos.y += speed * ts;
            }
            else if (Input.IsKeyDown(KeyCode.KINK_KEY_S))
            {
                pos.y -= speed * ts;
            }
            position = pos;
        }
        void OnDestroy() { 
            Console.WriteLine("OnDestroy called");
        }
    }
}