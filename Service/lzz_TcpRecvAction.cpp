#include "lzz_TcpRecvAction.h"
#include "lzz_Heartbeat.h"
#include "lzz_Push.h"

lzz_TcpRecvAction::lzz_TcpRecvAction()
{
}

lzz_TcpRecvAction::lzz_TcpRecvAction(SOCKET* sk)
{
	_sk = *sk;
}

void lzz_TcpRecvAction::SetSKOCKET(SOCKET* sk)
{
	if (_sk != INVALID_SOCKET)
	{
		closesocket(_sk);
	}
	_sk = *sk;
}

lzz_TcpRecvAction::~lzz_TcpRecvAction()
{
	if (isRun != lzz_nullptr)
		*isRun = false;
	closesocket(_sk);
}

void lzz_TcpRecvAction::Start()
{
	if(isRun == lzz_nullptr)
		lzz_Thread::Start();
	_Start = true;
}

void lzz_TcpRecvAction::run()
{
//	lzz_out << "我被运行了：" <<  static_cast<void*>(this) << lzz_endline;
	bool runing = true;
	isRun = &runing;
	while (runing)
	{
		if (!_Start)
		{
			Sleep(1);
			continue;
		}
		lzz_SocketInterface* interface_sk = new lzz_ServerSocket(&_sk);
		if (interface_sk == lzz_nullptr) return;
		int DataLen = 0;
		SOCKADDR padd_sockaddr;
		lzz_Factory* f = lzz_nullptr;
		char* p_str = lzz_nullptr;
		ActionType type = ActionType::None;
		if (interface_sk->TcpRecv(&type, 4) && interface_sk->TcpRecv(&DataLen,4) && DataLen != 0)
		{
			char backData[1] = { 1 };
			//interface_sk->TcpSend(backData, 1);
			p_str = new char[DataLen];
			if (interface_sk->TcpRecv(p_str, DataLen))
			{
				switch (type)
				{
				case _ActionType::PushAction: //添加推送
					f = new lzz_Push();
					break;
				default: break;
				}
				if (f == lzz_nullptr)
					return;
				if (f)
				{
					f->init(interface_sk, nullptr, p_str, nullptr);
					f->onLoad();
					f->BindView();
				}
				lzz_Delete(f);
			}
			
		}
		lzz_Delete(interface_sk);
		_Start = false;
		isOk = true;
		
	}
}

