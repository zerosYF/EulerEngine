#pragma once
#include<tchar.h>
#include"EulerObjectBase.h"
#include"Component/ComponentBase.h"
namespace EulerEngine {
	class ClassInfo {
		const TCHAR* name;
		ClassInfo* base;
		ClassInfo(const TCHAR* name,ClassInfo* base) {
			this->name = name;
			this->base = base;
		}
		inline const TCHAR* GetName() {
			return name;
		}
		inline ClassInfo* GetBase() {
			return base;
		}
		inline bool isSameType(const ClassInfo& another) const{
			return (&another == this);
		}
		inline bool isMyBase(const ClassInfo& another) const{
			const ClassInfo* tmp = this;
			while (!tmp->isSameType(another)) {
				if (tmp->base) {
					tmp = tmp->base;
				}
				else {
					return false;
				}
			}
			return true;
		}
	};
	class GameObject :public EulerRef{
	public:
		vector<ComponentBase*> components;
		virtual ~GameObject() = 0;
		GameObject();
	};
}