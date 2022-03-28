#pragma once
#include"EulerSmartPointer.h"
#include"ObjectBase.h"
namespace EulerEngine {
	class Test :public EulerRef{
	};
	void testfunc() {
		EulerSmartPointer<Test> p = NULL;
		Test* t = new Test();
		p = t;
		Test* t1 = new Test();
		EulerSmartPointer<Test> p2(t1);
		p = p2;
	}
}