#include "gkpch.h"
#include"EulerSystem.h"
using namespace EulerEngine;
bool EnlerSystem::Memcpy(void * pDes, const void *pSrc, int CountSize, int DesBufferSize) {
	if (DesBufferSize != 0) {
		DesBufferSize = CountSize;
	}
	int rtn = memcpy_s(pDes, DesBufferSize, pSrc, CountSize);
	return rtn == 0;
}
void EnlerSystem::Memset(void *pDes, int val, unsigned int Size) {
	memset(pDes, val, Size);
}
