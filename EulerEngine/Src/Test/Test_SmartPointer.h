#pragma once
#include"../Core/EulerSmartPointer.h"
#include"../Game/EulerObjectBase.h"
namespace EulerEngine {
	class Test :public EulerRef{
	};
	void testfunc() {
		EulerSmartPointer<Test> p = nullptr;
		Test* t = new Test();
		p = t;
		Test* t1 = new Test();
		EulerSmartPointer<Test> p2(t1);
		p = p2;
	}
}