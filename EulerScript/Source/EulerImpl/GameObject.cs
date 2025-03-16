using System;
namespace EulerEngine {
    public class GameObject
    {
        public GameObject(ulong uuid) {
            this.uuid = uuid;
        }
        public readonly ulong uuid;
        public bool HasComponent<T>() where T : Component, new(){
            Type type = typeof(T);
            return InternalCalls.GameObject_HasComponent(uuid, type);
        }
        public T GetComponent<T>() where T : Component, new(){
            if (HasComponent<T>()) {
                T component = new T() { gameObject = this };
                return component;
            }
            return null;
        }
    }
}