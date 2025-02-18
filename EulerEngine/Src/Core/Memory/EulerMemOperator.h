#include"EulerMemManager.h"
namespace EulerEngine {
	inline void* operator new(size_t size) {
		return EulerMemObject::GetManager().Allocate(size);
	}
	inline void operator delete(void* ptr) {
		EulerMemObject::GetManager().Recycle(ptr);
	}
}
