#include "gkpch.h"
#include"EulerClassFactory.h"
namespace EulerEngine {
	/*void ClassFactory::register_class(const std::string& className,createObject method) {
		m_classMap[className] = method;
	}
	Object* ClassFactory::create_class(const std::string& className) {
		auto it = m_classMap.find(className);
		if (it != m_classMap.end()) {
			return it->second();
		}
		return nullptr;
	}
	void ClassFactory::register_field(const std::string& className, const std::string& fieldName, const std::string& fieldType, size_t offset) {
		m_classFieldsMap[className].push_back(new ClassField(fieldType,fieldName,offset ));
	}
	ClassField* ClassFactory::getClassField(const std::string& className, const std::string& fieldName) {
		for (auto field : m_classFieldsMap[className]) {
			if (field->name() == fieldName) {
				return field;
			}
		}
		return nullptr;
	}
	void ClassFactory::register_method(const std::string& className, const std::string& methodName,uintptr_t method) {
		m_classMethodsMap[className].push_back(new ClassMethod(methodName,method));
	}
	ClassMethod* ClassFactory::getClassMethod(const std::string& className, const std::string& methodName) {
		for (auto method : m_classMethodsMap[className]) {
			if (method->name() == methodName) {
				return method;
			}
		}
		return nullptr;
	}

	ClassField* Object::getField(const std::string& fieldName) {
		return Singleton<ClassFactory>::Instance()->getClassField(m_name, fieldName);
	}
	ClassMethod* Object::getMethod(const std::string& methodName) {
		return Singleton<ClassFactory>::Instance()->getClassMethod(m_name, methodName);
	}

	template<typename T>
	T Object::get(const std::string& fieldName) {
		ClassFactory *factory = Singleton<ClassFactory>::Instance();
		ClassField* field = factory->getField(m_name, fieldName);
		size_t offset = field->offset();
		value = *(T*)((unsigned char*)(this) + offset);
		return value;
	}
	template<typename T>
	void Object::set(const std::string& fieldName, T&value) {
		ClassFactory *factory = Singleton<ClassFactory>::Instance();
		ClassField* field = factory->getField(m_name, fieldName);
		size_t offset = field->offset();
		*(T*)((unsigned char*)(this) + offset) = value;
	}
	void Object::call(const std::string& methodName) {
		ClassFactory* factory = Singleton<ClassFactory>::Instance();
		ClassMethod* method = factory->getClassMethod(m_name, methodName);
		auto func = method->method();
		typedef std::function<void(decltype(this))> class_method;
		(*((class_method*)func))(this);
	}*/
	/*template<typename T>
	T Object::call(const std::string&methodName) {
		ClassFactory* factory = Singleton<ClassFactory>::Instance();
		ClassMethod* method = factory->getClassMethod(m_name, methodName);
		auto func = method->method();
		typedef std::function<void(decltype(this))> class_method;
		(*((class_method*)func))(this);
	}
	template<typename T,typename T1>
	T Object::call(const std::string& methodName,T1& parm) {
		ClassFactory* factory = Singleton<ClassFactory>::Instance();
		ClassMethod* method = factory->getClassMethod(m_name, methodName);
		auto func = method->method();
		typedef std::function<void(decltype(this),parm)> class_method;
		(*((class_method*)func))(this,parm);
	}
	template<typename T, typename T1,typename T2>
	T Object::call(const std::& methodName, T1& parm1,T2& parm2) {
		ClassFactory* factory = Singleton<ClassFactory>::Instance();
		ClassMethod* method = factory->getClassMethod(m_name, methodName);
		auto func = method->method();
		typedef std::function<void(decltype(this),parm1,parm2)> class_method;
		(*((class_method*)func))(this, parm1,parm2);
	}*/
}