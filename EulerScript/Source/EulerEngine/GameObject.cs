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
        public static GameObject FindGameObjectByName(string name) {
            ulong uuid = InternalCalls.GameObject_FindGameObjectByName(name);
            if (uuid == 0) {
                return null;
            }
            GameObject gameObject = new GameObject(uuid);
            return gameObject;
        }
        public Transform transform
        {
            get
            {
                Transform transform = GetComponent<Transform>();
                return transform;
            }
        }
        public T As<T>() where T : Component, new()
        {
            object instance = InternalCalls.GameObject_GetScriptInstance(uuid);
            return instance as T;
        }
    }
}