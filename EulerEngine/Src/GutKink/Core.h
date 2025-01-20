#pragma once
#ifdef KINK_PLATFORM_WINDOWS
#ifdef KINK_DYNAMIC_LINK
#ifdef KINK_BUILD_DLL
#define KINK_API __declspec(dllexport)
#else
#define KINK_API __declspec(dllimport)
#endif
#else
#define KINK_API
#endif
#else
#error this engine only supports windows
#endif
#ifdef KINK_ENABLE_ASSERTS
#define KINK_ASSERT(x, ...) { if(!(x)) {KINK_ERROR("Assertion Failed:{0}",__VA_ARGS__); __debugbreak();}}
#define KINK_CORE_ASSERT(x, ...) { if(!(x)) {KINK_CORE_ERROR("Assertion Failed:{0}",__VA_ARGS__); __debugbreak();}}
#else
#define KINK_ASSERT(x, ...)
#define KINK_CORE_ASSERT(x, ...)
#endif
#define BIT(x) (1 << x)

#define KINK_BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)
#include<memory>
namespace EulerEngine {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename... Args>
	Scope<T> CreateScope(Args&&... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename... Args>
	Ref<T> CreateRef(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}