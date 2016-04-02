#include "lzz_ServerSocket.h"


lzz_ServerSocket::lzz_ServerSocket()
{
}

lzz_ServerSocket::lzz_ServerSocket(SOCKET *s)
{
	sk = *s;
}

void lzz_ServerSocket::Accept(SOCKET* s, SOCKADDR* address)
{
		*s = accept(this->sk,address,&serverAddr_len);
}
void lzz_ServerSocket::TcpBind(int port)
{

	ZeroMemory(reinterpret_cast<char *>(&serverAddr), sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);           /*本地监听端口*/
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); /*有IP*/
	sk = socket(AF_INET, SOCK_STREAM, 0);
	bind(sk, reinterpret_cast<struct sockaddr *>(&serverAddr), sizeof(serverAddr));
	listen(sk, 5000);
}

bool lzz_ServerSocket::TcpSend(void* pData,int len)
{
	int state = send(sk, static_cast<char*>(pData), len, 0);
	return state == len;
}

bool lzz_ServerSocket::TcpRecv(void* pData,int len)
{
	for (int i = 0; i < len;i++)
	{
		if(	recv(sk, static_cast<char*>(pData) + i, 1, 0) <= 0)
		{
			return false;
		}
	}
	return true;
}

void lzz_ServerSocket::UdpBind(int port)
{
	ZeroMemory(reinterpret_cast<char *>(&serverAddr), sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);           /*本地监听端口*/
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); /*有IP*/
	sk = socket(AF_INET, SOCK_DGRAM, 0);
	bind(sk, reinterpret_cast<SOCKADDR*>(&serverAddr), sizeof(serverAddr));
}


void lzz_ServerSocket::UdpSend(void* pData, int len, ActionType at, SOCKADDR* pAddress)
{
	char *s = new char[len + 8];
	lzz_ZeroMemory(s, len + 8);
	lzz_Memcpy(&(s[0]), &at, 4);
	lzz_Memcpy(&(s[4]), &len, 4);
	lzz_Memcpy(&(s[8]), pData, len);
	sendto(sk, s, len + 8, 0, pAddress, sizeof(SOCKADDR));
	lzz_Deletes(s);
}

void lzz_ServerSocket::UdpRecv(void* pData,int len, SOCKADDR* pAddress)
{
	recvfrom(sk, static_cast<char*>(pData), len, 0, pAddress, &serverAddr_len);//from收到客户端的IP信息
}

lzz_ServerSocket::~lzz_ServerSocket()
{
	if (sk != INVALID_SOCKET)
	{
		shutdown(sk,2);
	}
}
