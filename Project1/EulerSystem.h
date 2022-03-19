#include<memory.h>
namespace EulerEngine
{
	class EnlerSystem {
	public:
		bool Memcpy(void * pDes, const void *pSrc, int CountSize, int DesBufferSize = 0) {
			if (DesBufferSize != 0) {
				DesBufferSize = CountSize;
			}
			int rtn = memcpy_s(pDes, DesBufferSize, pSrc, CountSize);
			return rtn == 0;
		}
		void Memset(void *pDes,int val,unsigned int Size) {
			memset(pDes,val,Size);
		}
	};
}