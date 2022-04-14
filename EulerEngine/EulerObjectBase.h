#pragma once
namespace EulerEngine {
	class EulerRef {
	private:
		int refCount;
	public:
		EulerRef() {
			refCount = 0;
		}
		~EulerRef() {
			refCount = 0;
		}
		inline int GetRef() const {
			return refCount;
		}
		inline void IncreRef() {
			refCount++;
		}
		inline void DecreRef() {
			refCount--;
			if (refCount == 0) delete this;
		}
	};
}