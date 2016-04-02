#include "lzz_RecvThread.h"
#include "../include/lzz_ClientList.h"
#include "../include/lzz_Factory.h"
#include "lzz_Heartbeat.h"
#include "lzz_Push.h"


lzz_RecvThread::lzz_RecvThread(lzz_SocketInterface* s,lzz_ClientList *l)
{
	sk = s;
	cl = l;
	isRun = lzz_nullptr;
}

lzz_RecvThread::~lzz_RecvThread()
{
	*isRun = false;
}

void lzz_RecvThread::run()
{
	bool run_bool = true;
	isRun = &run_bool;
	char pRecvData[1024];
	int DataLen = 0;
	SOCKADDR padd_sockaddr;
	while (run_bool) {
		lzz_Factory * f = lzz_nullptr;
		char* p_str = lzz_nullptr;
		lzz_ZeroMemory(pRecvData, 1024);
		lzz_ZeroMemory(&padd_sockaddr, sizeof(SOCKADDR));
		sk->UdpRecv(pRecvData, 1024, &padd_sockaddr);
		ActionType type = *reinterpret_cast<ActionType*>(pRecvData);
		DataLen = *reinterpret_cast<int*>(&pRecvData[4]);
		switch (type)
		{
		case Heartbeat: //心跳包
			f = new lzz_Heartbeat();
			break;
		case PushAction: //添加好友推送
			f = new lzz_Push();
			break;
		default: break;
		}
		if (f) {
			p_str = new char[DataLen];
			lzz_Memcpy(p_str, &pRecvData[8], DataLen);
			f->init(sk, cl, p_str, &padd_sockaddr);
			f->onLoad();
			f->BindView();
		}
		lzz_Delete(f);
	}
}

void lzz_RecvThread::Close()
{
	this->lzz_Thread::Close();

}
