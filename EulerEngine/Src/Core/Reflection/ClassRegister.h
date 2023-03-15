#pragma once
#include"EulerClassFactory.h"
namespace EulerEngine {
	class ClassRegister {
	public:
		ClassRegister(const std::string &className, createObject method) {
			Singleton<ClassFactory>::Instance()->register_class(className, method);
		}
		ClassRegister(const std::string&className, const std::string&fieldName, const std::string& fieldType, size_t offset) {
			Singleton<ClassFactory>::Instance()->register_field(className, fieldName, fieldType, offset);
		}
		ClassRegister(const std::string&className, const std::string&methodName, uintptr_t method) {
			Singleton<ClassFactory>::Instance()->register_method(className, methodName, method);
		}
	};
#define OFFSET(object,fieldName)\
	(size_t)(&(object.fieldName))-(size_t)(&object)

#define REGISTER_CLASS(className)\
	Object* createObjectBy##className(){\
		Object* obj = new className();\
		obj->setClassName(#className);\
		return obj;\
	}\
	ClassRegister	classRegister##className(#className,createObjectBy##className)

#define REGISTER_FIELD(className,fieldName,fieldType)\
	className className##fieldName;\
	ClassRegister classRegister##className##fieldName(#className,#fieldName,#fieldType,OFFSET(className##fieldName,fieldName))

#define REGISTER_METHOD(className,methodName)\
	std::function<void(className*)> className##methodName = &className::methodName;\
	ClassRegister classRegister##className##methodName(#className,#methodName,(uintptr_t)&(className##methodName))
}