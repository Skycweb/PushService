#include "lzz_Thread.h"



lzz_Thread::lzz_Thread()
{
}


lzz_Thread::~lzz_Thread()
{

}

void lzz_Thread::Start()
{
	hThread = reinterpret_cast<HANDLE>(lzz_Beginthread(agent, static_cast<void *>(this)));
}
void lzz_Thread::run()
{
	lzz_out << "Base Thread" << lzz_endline;
}
void lzz_Thread::agent(void *p)
{
	lzz_Thread *agt = static_cast<lzz_Thread *>(p);
	agt->run();
}
HANDLE lzz_Thread::getThread()
{
	return hThread;
}

void lzz_Thread::Sleep(unsigned long s)
{
	lzz_sleep(s);
}

void lzz_Thread::Close()
{
	isClose = true;
}

bool lzz_Thread::getState()
{
	return isClose;
}
