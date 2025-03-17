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
    public class Rigidbody2D : Component { 
        public void ApplyLinearImpulse(Vector2 impulse) {
            InternalCalls.Rigidbody2D_ApplyLinearImpulse(gameObject.uuid, ref impulse);
        }
        public void ApplyAngularImpulse(float impulse) {
            InternalCalls.Rigidbody2D_ApplyAngularImpulse(gameObject.uuid, ref impulse);
        }
    }
}