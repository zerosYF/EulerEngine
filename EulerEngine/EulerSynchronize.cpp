#include"EulerSynchronize.h"
#include<windows.h>
#include<assert.h>
using namespace EulerEngine;
EulerCriticalSection::EulerCriticalSection() {
	InitializeCriticalSection(&section);
	SetCriticalSectionSpinCount(&section, 4000);
	//自旋锁减轻切换负担
}
EulerCriticalSection::~EulerCriticalSection() {
	DeleteCriticalSection(&section);
}
void EulerCriticalSection::Enter(void) {
	EnterCriticalSection(&section);
}
void EulerCriticalSection::Leave(void) {
	LeaveCriticalSection(&section);
}

EulerSemaphore::EulerSemaphore(unsigned int InitCount,unsigned int MaxCount) {
	assert(InitCount<=MaxCount);
	this->semaphore = CreateSemaphore(NULL,InitCount,MaxCount,NULL);
	this->maxCount = MaxCount;
	assert(semaphore);
}
EulerSemaphore::~EulerSemaphore() {
	bool result = CloseHandle(semaphore);
	semaphore = NULL;
	assert(result);
}
void EulerSemaphore::Enter() {
	DWORD result = WaitForSingleObject(semaphore,INFINITE);
	//windows下创建的对象会被赋予状态量，object正在使用无信号，object等待被使用是有信号；
	assert(result);
}
void EulerSemaphore::Leave(unsigned int leaveCOunt) {
	bool result = ReleaseSemaphore(semaphore,leaveCOunt,NULL);
}
EulerMutex::EulerMutex() {
	this->mutex = CreateMutex(NULL,false,NULL);
	assert(mutex);
}
EulerMutex::~EulerMutex() {
	bool result = CloseHandle(mutex);
	mutex = NULL;
	assert(result);
}
void EulerMutex::Enter() {
	DWORD result = WaitForSingleObject(mutex,INFINITE);
	assert(result!=WAIT_FAILED);
}
void EulerMutex::Leave() {
	bool result = ReleaseMutex(mutex);
	assert(result);
}
