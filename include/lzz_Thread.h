#pragma once
#include "base.h"
#include "lzz_Object.h"

typedef void *HANDLE;
class lzz_Thread:public lzz_Object
{
public:
	lzz_Thread();
	virtual ~lzz_Thread();
	virtual void Start();
	virtual void run();
	HANDLE getThread();
	static void Sleep(unsigned long s);
	virtual void Close();
	bool getState();
private:
	HANDLE hThread;
	bool isClose = false;
	static void agent(void *p);
};

