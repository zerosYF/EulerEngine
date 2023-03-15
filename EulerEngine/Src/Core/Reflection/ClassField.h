#pragma once
#include<string>
namespace EulerEngine {
	class ClassField {
	public:
		ClassField() : m_type(""), m_name(""), m_offset(0) {}
		ClassField(const std::string &type, const std::string &name, size_t offset) : m_type(type), m_name(name), m_offset(offset) {}
		~ClassField() {}
		const std::string& name() { return m_name; }
		const std::string& type() { return m_type; }
		size_t& offset() { return m_offset; }
	private:
		std::string m_type;
		std::string m_name;
		size_t m_offset;
	};
}