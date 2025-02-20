#pragma once
#include"EulerObject.h"
namespace EulerEngine {
	class EulerBehaviour {
	public:
		virtual ~EulerBehaviour() {}
		template<typename T>
		T& GetComponent() {
			return m_gameObject.GetComponent<T>();
		}
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(TimerSystem ts) {}
	private:
		GameObject m_gameObject;
		friend class Scene;
	};
}