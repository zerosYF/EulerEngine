using EulerEngine;
using System;

namespace Sandbox { 
    public class CameraController:EulerBehaviour {
        private GameObject another;
        public float DistanceFromPlayer = 5.0f;
        void OnCreate() {
            Console.WriteLine("Camera OnCreate called:" + this.gameObject.uuid);
            transform.position = new Vector3(transform.position.x, transform.position.y, DistanceFromPlayer);
            //another = GameObject.FindGameObjectByName("Circle");
        }
        void OnUpdate(float ts)
        {
            if (another == null) return;
            //transform.position = new Vector3(another.transform.position.XY, DistanceFromPlayer);
        }
    }
}