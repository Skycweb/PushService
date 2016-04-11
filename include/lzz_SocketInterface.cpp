#include "lzz_SocketInterface.h"


int lzz_SocketInterface::SocketLen = 0;
int lzz_SocketInterface::SocketStartup = 1;
WSADATA lzz_SocketInterface::wsa;
lzz_SocketInterface::lzz_SocketInterface()
{
	if (SocketLen == 0 && SocketStartup == 1)
	{
#ifdef  _IOCP_
		SocketStartup = WSAStartup(0x0202, &wsa);
#else
		SocketStartup = WSAStartup(MAKEWORD(1, 1), &wsa);
#endif
		/*��ʼ��socket��Դ*/
		if (SocketStartup != 0)
		{
			lzz_out << "��ʼ��socket��Դ��ʧ��" << lzz_endline;
			lzz_out << "��رճ�����¿�ʼ" << lzz_endline;
		}
	}
	SocketLen++;
}

lzz_SocketInterface::~lzz_SocketInterface()
{
	SocketLen--;
	if(SocketLen == 0)
	{
		WSACleanup();
		SocketStartup = 1;
	}
}

void lzz_SocketInterface::Accept(SOCKET* s, SOCKADDR* address)
{
}

bool lzz_SocketInterface::TcpSend(void* pData, int len)
{
	return false;
}

bool lzz_SocketInterface::TcpSend(void* pData, int len, lzz_Factory* f, int ActionType)
{
	return false;
}

bool lzz_SocketInterface::TcpSend(void* pData, int len, ActionType a)
{
	return false;
}

bool lzz_SocketInterface::TcpRecv(void* pData, int len)
{
	return false;
}

bool lzz_SocketInterface::TcpRecv(void* pData, int len, lzz_Factory* f, int ActionType)
{
	return false;
}

void lzz_SocketInterface::UdpSend(void* pData, int len, ActionType at, SOCKADDR* pAddress)
{
}


void lzz_SocketInterface::UdpSend(void* pData, int len, ActionType at)
{
}

void lzz_SocketInterface::UdpRecv(void* pData, int len, SOCKADDR* pAddress)
{
}
