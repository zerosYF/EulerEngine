#pragma once
#include<memory.h>
namespace EulerEngine
{
	class EnlerSystem {
	public:
		bool Memcpy(void * pDes, const void *pSrc, int CountSize, int DesBufferSize = 0);
		void Memset(void *pDes, int val, unsigned int Size);
	};
}