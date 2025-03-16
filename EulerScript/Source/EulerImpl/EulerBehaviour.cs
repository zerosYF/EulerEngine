using System;
using System.Runtime.CompilerServices;
namespace EulerEngine {
    public class EulerBehaviour
    {
        protected EulerBehaviour() {
            gameObject = new GameObject(1);
        }
        internal EulerBehaviour(ulong uuid) {
            gameObject = new GameObject(uuid);
        }
        public GameObject gameObject;
        public Transform transform
        {
            get {
                Transform transform = gameObject.GetComponent<Transform>();
                return transform;
            }
        }
    };
}