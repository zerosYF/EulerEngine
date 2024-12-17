#include "../gkpch.h"
#include"EulerMemManager.h"
#include<stdlib.h>
#include<assert.h>
using namespace EulerEngine;
void* EulerBlock::FillBlockMask() {
	unsigned int *ptr = (unsigned int*)this;
	//跳过block信息区；
	unsigned int *beginMask_ptr = ptr + sizeof(EulerBlock);
	//数据区头部标志填充;
	*beginMask_ptr = BEGIN_MASK;
	unsigned int *data_ptr = ptr + sizeof(unsigned int*);
	unsigned int *endMask_ptr = data_ptr + size;
	//数据区尾部标志填充；
	*endMask_ptr = END_MASK;
	return data_ptr;
}
void* EulerMemManager::Allocate(unsigned int size) {
	unsigned int SumSize = sizeof(EulerBlock)
		+ sizeof(unsigned int) + size + sizeof(unsigned int);
	char* ptr = (char*) malloc(SumSize);
	if (!ptr) return NULL;
	EulerBlock *block = (EulerBlock*)ptr;
	block->SetSize(size);
	AddBlock(block);
	void* rtn_ptr = block->FillBlockMask();
	return rtn_ptr;
}
void EulerMemManager::Recycle(void* data_ptr) {
	if (!data_ptr) return;
	unsigned int* beginMask_ptr = (unsigned int*)data_ptr- sizeof(unsigned int*);
	assert(*beginMask_ptr==BEGIN_MASK);
	EulerBlock *block_ptr = (EulerBlock*)beginMask_ptr - sizeof(EulerBlock);
	unsigned int* endMask_ptr = (unsigned int*)data_ptr + block_ptr->GetSize();
	assert(*endMask_ptr==END_MASK);
	RemoveBlock(block_ptr);
	free(data_ptr);
}
void EulerMemManager::AddBlock(EulerBlock *block) {
	if (pTail) {
		pTail->next = block;
		block->pre = pTail;
		pTail = block;
	}
	else {
		pHead = block;
		pTail = block;
	}
}
void EulerMemManager::RemoveBlock(EulerBlock *block) {
	if (block->next) {
		block->next->pre = block->pre;
	}
	else {
		pTail = block->pre;
	}
	if (block->pre) {
		block->pre->next = block->next;
	}
	else {
		pHead = block->next;
	}
}