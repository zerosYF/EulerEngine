#include<Windows.h>
namespace EulerEngine {
	class EulerCriticalSection {
	public:
		CRITICAL_SECTION section;
		//临界区
		EulerCriticalSection(void);
		~EulerCriticalSection(void);
		void Enter(void);
		void Leave(void);
	};
	//信号量；
	class EulerSemaphore {
	protected:
		HANDLE semaphore;
		unsigned int maxCount;
	public:
		EulerSemaphore(unsigned int InitCount, unsigned int MaxCount);
		~EulerSemaphore();
		void Leave(unsigned int leaveCount);
		void Enter();
		inline void* GetHandle() {
			return semaphore;
		}
	};
	//互斥量；
	class EulerMutex {
	protected:
		HANDLE mutex;
	public:
		EulerMutex();
		~EulerMutex();
		void Leave();
		void Enter();
		inline void* GetHandle() {
			return mutex;
		}
	};
}
