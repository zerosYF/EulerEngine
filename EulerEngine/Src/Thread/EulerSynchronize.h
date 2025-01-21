#include<Windows.h>
namespace EulerEngine {
	class EulerCriticalSection {
	public:
		CRITICAL_SECTION section;
		//�ٽ���
		EulerCriticalSection(void);
		~EulerCriticalSection(void);
		void Enter(void);
		void Leave(void);
	};
	//�ź�����
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
	//��������
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
