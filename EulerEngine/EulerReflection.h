#pragma once
#include<tchar.h>
namespace EulerEngine {
	class ClassProperty {
	private:
		unsigned int Flag;
		unsigned int ElementOffset;
		const TCHAR* name;
		ClassProperty(const TCHAR* name,unsigned int Flag,unsigned int ElementOffset) {
			this->name = name;
			this->Flag = Flag;
			this->ElementOffset = ElementOffset;
		}
		void* GetValueAddress(void* Obj) {
			return (void*)((char*)Obj+ElementOffset);
		}
	};
}