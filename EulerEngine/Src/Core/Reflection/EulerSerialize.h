#pragma once
#include<vector>
#include<json11/json11.hpp>
namespace EulerEngine {
	using EulerJson = json11::Json;
	template<typename...>
	class Serialize {
	public:
		template<typename T>
		static EulerJson writePointer(T* instance) {
			return EulerJson::object{};
		}
		template<typename T>
		static T& readPointer(const EulerJson& json,T*& instance) {
		}
		template<typename T>
		static EulerJson write() {
		}
		template<typename T>
		static T*& read() {
		}
	};
}