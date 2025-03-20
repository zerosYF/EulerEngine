using System;
using EulerEngine;
namespace Sandbox {
    public class Player:EulerBehaviour {
        private Rigidbody2D rb;
        public float speed = 1.0f;
        public float val = 2.0f;
        void OnCreate() { 
            Console.WriteLine("Player OnCreate called:" + this.gameObject.uuid);
            rb = gameObject.GetComponent<Rigidbody2D>();
            speed = 100.0f;
        }
        void OnUpdate(float ts) {
            if (rb == null) {
                return;
            }
            if (Input.IsKeyDown(KeyCode.KINK_KEY_W))
            {
                Vector2 vec = new Vector2(0.0f, 1.0f);
                rb.ApplyLinearImpulse(vec * speed);
                Console.WriteLine("Applying impulse: " + vec * speed);
            }
            else if (Input.IsKeyDown(KeyCode.KINK_KEY_S))
            {
                Vector2 vec = new Vector2(0.0f, -1.0f);
                rb.ApplyLinearImpulse(vec * speed);
                Console.WriteLine("Applying impulse: " + vec * speed);
            }
        }
        void OnDestroy() { 
            Console.WriteLine("OnDestroy called" + this.gameObject.uuid);
        }
    }
}