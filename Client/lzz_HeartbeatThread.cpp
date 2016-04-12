#include "lzz_HeartbeatThread.h"



lzz_HeartbeatThread::lzz_HeartbeatThread(lzz_ClientSocket *s)
{
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
		sk->UdpSend(&lzz_UserId, 16, ActionType::Heartbeat);
		//lzz_out << "�ҷ�����������:" << lzz_endline;
		Sleep(1000*10);
	}
}
