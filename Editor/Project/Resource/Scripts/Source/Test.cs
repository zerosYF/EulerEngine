using System;
using EulerEngine;
namespace Sandbox {
    public class Test:EulerBehaviour {
        private Rigidbody2D rb;
        void OnCreate() { 
            Console.WriteLine("OnCreate called:" + this.gameObject.uuid);
            rb = gameObject.GetComponent<Rigidbody2D>();
        }
        void OnUpdate(float ts) {
            Console.WriteLine("OnUpdate called with ts = " + ts);
            float speed = 8.5f;
            if (rb == null) {
                return;
            }
            if (Input.IsKeyDown(KeyCode.KINK_KEY_W))
            {
                Vector2 vec = new Vector2(0.0f, 1.0f);
                rb.ApplyLinearImpulse(vec * speed);
            }
            else if (Input.IsKeyDown(KeyCode.KINK_KEY_S))
            {
                Vector2 vec = new Vector2(0.0f, -1.0f);
                rb.ApplyLinearImpulse(vec * speed);
            }
        }
        void OnDestroy() { 
            Console.WriteLine("OnDestroy called");
        }
    }
}