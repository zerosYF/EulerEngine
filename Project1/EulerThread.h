#include<Windows.h>
namespace EulerEngine {
	class EulerThread {
	public:
		enum Priorty {
			LOW,
			MID,
			HEIGHT,
		};
		enum State {
			START,
			SUSPEND,
			STOP,
		};
	private:
		void* Thread;
		Priorty priorty;
		unsigned int StackSize;
	protected:
		State state;
	public:
		void SetPriorty(Priorty p);
		Priorty GetPriorty();
		void SetStackSize(unsigned int size);
		unsigned int GetStackSize();
		void Start();
		void Suspend();
		void Sleep(DWORD millionSecond);
		void Stop();
		State GetThreadState() {
			return state;
		}
	protected:
		virtual void Run() = 0;//´¿Ðéº¯Êý
		virtual const TCHAR* GetThreadName() {
		}
	};
}