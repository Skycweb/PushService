#include "lzz_RunStart.h"




lzz_RunStart::lzz_RunStart()
{
	sk = new lzz_ClientSocket();
	if (!(sk->UdpBind(lzz_ServiceUdpId, lzz_ServiceUdpPort)))
	{
		lzz_out << "连接服务器不成功" << lzz_endline;
		return;
	}
}

lzz_ClientSocket* lzz_RunStart::getSOCKET()
{
	return sk;
}

void lzz_RunStart::run()
{
	bool run = true;
	isRun = &run;
	char pRecvData[1024];
	int DataLen = 0;
	SOCKADDR padd_sockaddr;
	while (run) {
		lzz_Factory * f = nullptr;
		char* p_str = nullptr;
		lzz_ZeroMemory(pRecvData, 1024);
		lzz_ZeroMemory(&padd_sockaddr, sizeof(SOCKADDR));
		sk->UdpRecv(pRecvData, 1024, &padd_sockaddr);
		lzz_out << "收到来自：" << inet_ntoa(((SOCKADDR_IN*)&(padd_sockaddr))->sin_addr) << ":" << ((SOCKADDR_IN*)&(padd_sockaddr))->sin_port << "的连接"  << lzz_endline;

		ActionType type = *reinterpret_cast<ActionType*>(pRecvData);
		DataLen = *reinterpret_cast<int*>(&pRecvData[4]);
		switch (type)
		{
		case _ActionType::Heartbeat: break;
		case _ActionType::PushAction: 
			f = new lzz_Push();
			break;
		case ActionType::PushMsg:
			f = new lzz_SendMsg();
			break;
		default: break;
		}
		if (f) {
			p_str = new char[DataLen];
			lzz_Memcpy(p_str, &pRecvData[8], DataLen);
			f->init(sk, lzz_nullptr, p_str, &padd_sockaddr);
			f->onLoad();
			f->BindView();
		}
		lzz_Delete( f);
	}
	
}

lzz_RunStart::~lzz_RunStart()
{
	*isRun = false;
}
