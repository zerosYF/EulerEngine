#define CALL_STACK_SIZE 32
#define BEGIN_MASK 0x77777777
#define END_MASK 0X77777777
#define RECORD_SIZE 64
namespace EulerEngine {
	class EulerBlock {
	private:
		//sizeof(EulerBlock)只与成员变量有关
		void *ptr[CALL_STACK_SIZE];
		unsigned int size;
	public:
		EulerBlock *pre;
		EulerBlock *next;
	public:
		inline void SetSize(unsigned int size) {
			this->size = size;
		}
		inline unsigned int GetSize() {
			return size;
		}
		void* FillBlockMask();
	};
	class EulerMemManager {
	private:
		unsigned int newCount;
		unsigned int deleteCount;
		unsigned int blockCount;
		unsigned int byteCount;
		unsigned int MaxByteCount;
		unsigned int MaxBlockCount;
		unsigned int SizeRecord[RECORD_SIZE];
		EulerBlock *pHead;
		EulerBlock *pTail;
	public:
		void *Allocate(unsigned int size);
		void Recycle(void* dataPtr);
	private:
		void AddBlock(EulerBlock *block);
		void RemoveBlock(EulerBlock *block);
	};
	class EulerMemObject {
	private:
		static EulerMemManager manager;
	public:
		static EulerMemManager& GetManager() {
			return manager;
		}
	};
}
