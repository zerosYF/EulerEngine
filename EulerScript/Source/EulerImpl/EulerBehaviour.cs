using System;
using System.Runtime.CompilerServices;
namespace EulerEngine {
    public class EulerBehaviour
    {
        protected EulerBehaviour() {
            gameObject = new GameObject(0);
        }
        internal EulerBehaviour(ulong uuid) {
            gameObject = new GameObject(uuid);
        }
        public readonly GameObject gameObject;
        public Transform transform
        {
            get {
                Transform transform = gameObject.GetComponent<Transform>();
                return transform;
            }
        }
    };
}