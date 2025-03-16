namespace EulerEngine {
    public abstract class Component {
        public GameObject gameObject { get; internal set; }
    }
    public class Transform:Component { 
        public Vector3 position {
            get {
                InternalCalls.Transform_GetPosition(gameObject.uuid, out Vector3 position);
                return position;
            }
            set { 
                InternalCalls.Transform_SetPosition(gameObject.uuid, ref value);
            } 
        }
    }
}