#include "lzz_TcpRecv.h"
#include "lzz_TcpRecvAction.h"

lzz_TcpRecv::lzz_TcpRecv(lzz_SocketInterface* s)
{
	sk = s;
}

lzz_TcpRecv::~lzz_TcpRecv()
{
	*isRun = false;
}

void lzz_TcpRecv::run()
{
//	lzz_out << "进入等待接入" << lzz_endline;
	bool _Run = true;
	isRun = &_Run;
	SOCKET _socket;
	SOCKADDR address;
	lzz_ZeroMemory(&_socket,sizeof(SOCKET));
	while (_Run)
	{
		sk->Accept(&_socket, &address);
		if (_socket == INVALID_SOCKET)
			break;
//		lzz_out << "收到一个连接接入" << lzz_endline;
		lzz_TcpRecvAction* a = getAction();
		if (a != lzz_nullptr) {
			a->SetSKOCKET(&_socket);
			a->Start();
		}
	}
}

lzz_TcpRecvAction* lzz_TcpRecv::getAction()
{
	int len = 0;
	lzz_ARRAY_LEN(tcpAction, len);
	for (int i = 0; i < len;i++)
	{
		if (tcpAction[i].isOk)
		{
			tcpAction[i].isOk = false;
			return &(tcpAction[i]);
		}
		if (i == len-1)
			i = 0;
	}
	return lzz_nullptr;
}
