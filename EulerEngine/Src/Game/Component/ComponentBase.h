#pragma once
#include"../EulerObject.h"
#include<memory>
using namespace std;
namespace EulerEngine {
	class ComponentBase {
	/*protected:
		weak_ptr<GameObject> m_parent;
		bool m_isDirty{ false };
		bool m_enableUpdateInEditorMode{false};
	public:
		ComponentBase() = default;
		virtual ~ComponentBase() = 0;
		virtual void update() = 0;
		bool isDirty() const {
			return m_isDirty;
		}
		bool enableUpdateInEditorMode() const {
			return m_enableUpdateInEditorMode;
		}*/
	};
}