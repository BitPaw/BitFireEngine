#include "AsyncLock.h"

BF::AsyncLock::AsyncLock()
{
	LockClear(&_lockID);
}

BF::AsyncLock::~AsyncLock()
{
	LockDelete(&_lockID);
}

int BF::AsyncLock::Create()
{
	return LockCreate(&_lockID);
}

int BF::AsyncLock::Delete()
{
	return LockDelete(&_lockID);
}

int BF::AsyncLock::Lock()
{
	return LockLock(&_lockID);
}

int BF::AsyncLock::Release()
{
	return LockRelease(&_lockID);
}
