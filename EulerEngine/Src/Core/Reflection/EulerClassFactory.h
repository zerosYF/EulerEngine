#pragma once
#include<unordered_map>
#include<map>
#include<functional>
#include"ClassField.h"
#include"ClassMethod.h"
#include<string>
namespace EulerEngine {
	class Object {
	public:
		Object() {}
		~Object() {}
		void setClassName(const std::string& className) { m_name = className; }
		const std::string& getClassName() const { return m_name; }
		virtual void show() = 0;
		//类字段；
		ClassField* getField(const std::string& fieldName);
		template<typename T>
		T get(const std::string&fieldName);
		template<typename T>
		void set(const std::string&fieldName, T&value);
		//类方法；
		ClassMethod* getMethod(const std::string& methodName);
		void call(const std::string&methodName);
		/*template<typename T>
		T call(const std::string& methodName);
		template<typename T,typename T1>
		T call(const std::string& methodName,T1& parm);
		template<typename T, typename T1,typename T2>
		T call(const std::string& methodName, T1& parm1,T2& parm2);*/
	private:
		std::string m_name;
	};
	typedef Object* (*createObject)(void);

	class ClassFactory {
	public: 
		void register_class(const std::string& className,createObject method);
		Object* create_class(const std::string& className);

		void register_field(const std::string& className,const std::string& fieldName,const std::string& fieldType,size_t offset);
		ClassField* getClassField(const std::string& className,const std::string& fieldName);

		void register_method(const std::string& className,const std::string& methodName,uintptr_t method);
		ClassMethod* getClassMethod(const std::string& className,const std::string& methodName);
	private:
		ClassFactory() {}
		~ClassFactory(){}
	private:
		std::unordered_map<std::string, createObject> m_classMap;
		std::unordered_map<std::string, std::vector<ClassField*>> m_classFieldsMap;
		std::unordered_map<std::string, std::vector<ClassMethod*>> m_classMethodsMap;
	};
}
