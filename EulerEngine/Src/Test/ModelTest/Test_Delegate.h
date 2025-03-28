#include"../../Core/EulerDelegate.h"
#include<iostream>
namespace EulerEngine {
	int Add(int a,int b) {
		return a + b;
	}
	class TestA {
	public:
		TestA() {
		}
		int CAdd(int a,int b) {
			return a + b;
		}
	};
	void delegate_test() {
		EulerDelegate<int, int, int> dgt;
		dgt.BindNormalFunc(Add);
		int ans = dgt.Execute(1, 2);
		std::cout << ans << std::endl;
		TestA test;
		EulerDelegate<int, int, int> dgt1;
		dgt1.BindMemberFunc<TestA>(&test,Add);
		ans = dgt1.Execute(2, 3);
		std::cout << ans << std::endl;
	}
}
