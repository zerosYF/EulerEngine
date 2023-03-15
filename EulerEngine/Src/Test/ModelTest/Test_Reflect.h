#pragma once
#include"../../Core/Reflection/ClassRegister.h"
#include<iostream>
namespace EulerEngine {
	class A :public Object {
	public:
		std::string ss;
		int a;
	public:
		A(): ss("i love you"),a(10){}
		void show() {
			std::cout << ss << " " << a << std::endl;
		}
		void f1() {
			std::cout << "this is f1" << std::endl;
		}
		int f2() {
			std::cout << "this is f2" << std::endl;
			int rtn = 2;
			return rtn;
		}
		int f3(int a) {
			std::cout << "this is f3" << std::endl;
			return a;
		}
	};
	REGISTER_CLASS(A);
	REGISTER_FIELD(A,ss,string);
	REGISTER_FIELD(A,a,int);
	REGISTER_METHOD(A, f1);

	void test() {
		ClassFactory *factory = Singleton<ClassFactory>::Instance();
		Object *a = factory->create_class("A");
		std::string name = a->getClassName();
		std::cout << name << std::endl;
		//a->set("ss","fuck you");
		a->call("f1");
		a->call("show");
		system("pause");
	}
}