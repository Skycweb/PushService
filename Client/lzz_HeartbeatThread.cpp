#include "lzz_HeartbeatThread.h"



lzz_HeartbeatThread::lzz_HeartbeatThread(lzz_ClientSocket *s)
{
	guid_id = s->getID();
	this->sk = s;
}


lzz_HeartbeatThread::~lzz_HeartbeatThread()
{
	if(is_close_b_)
		*is_close_b_ = false;
}



void lzz_HeartbeatThread::Close()
{
	this->lzz_Thread::Close();
}

void lzz_HeartbeatThread::run()
{
	bool run = true;
	is_close_b_ = &run;
	while(run)
	{
		sk->UdpSend(&guid_id, 16, Heartbeat);
		//lzz_out << "我发起了心跳包:" << lzz_endline;
		Sleep(1000*10);
	}
}
