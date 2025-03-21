using EulerEngine;
using System;

namespace Sandbox { 
    public class CameraController:EulerBehaviour {
        private GameObject another;
        public float DistanceFromPlayer = 5.0f;
        void OnCreate() {
            Console.WriteLine("Camera OnCreate called:" + this.gameObject.uuid);
            transform.position = new Vector3(transform.position.XY, DistanceFromPlayer);
            another = GameObject.FindGameObjectByName("Circle");
        }
        void OnUpdate(float ts)
        {
            if (another == null) return;
            Console.WriteLine("Camera OnUpdate called:" + this.gameObject.uuid);
            transform.position = new Vector3(another.transform.position.XY, DistanceFromPlayer + 10.0f);
        }
    }
}