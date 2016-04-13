#include "lzz_ServerSocket.h"


lzz_ServerSocket::lzz_ServerSocket()
{
}

lzz_ServerSocket::lzz_ServerSocket(SOCKET *s)
{
	sk = *s;
}

lzz_ServerSocket::lzz_ServerSocket(SOCKET* s, lzz_LPPER_HANDLE_DATA _phandle, lzz_LPPER_IO_OPERATION_DATA _pIo)
{
	y_pHaandle = _phandle;
	y_pIo = _pIo;
	sk = *s;
}

void lzz_ServerSocket::Accept(SOCKET* s, SOCKADDR* address)
{
#ifdef  _IOCP_
		*s = WSAAccept(this->sk, lzz_nullptr, lzz_nullptr , lzz_nullptr, 0);
#else
		*s = accept(this->sk, address, &serverAddr_len);
#endif
}
void lzz_ServerSocket::TcpBind(int port)
{

	ZeroMemory(reinterpret_cast<char *>(&serverAddr), sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);           /*本地监听端口*/
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); /*有IP*/
#ifdef  _IOCP_
	sk = WSASocketW(AF_INET, SOCK_STREAM, 0, lzz_nullptr, 0, WSA_FLAG_OVERLAPPED);;
#else
	sk = socket(AF_INET, SOCK_STREAM, 0);
#endif
	if(sk == SOCKET_ERROR)
	{
		throw 10001;
	}
	if(bind(sk, (sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		throw 10001;
	}
	if(listen(sk, 2000) == SOCKET_ERROR)
	{
		throw 10001;
	}
}


bool lzz_ServerSocket::TcpSend(void* pData,int len)
{
	if(y_pHaandle != lzz_nullptr)
	{
		lzz_Memcpy(y_pIo->buffer, pData, len);
		DWORD dwFlags = 0;
		DWORD lpNumberOfBytesSent = 0;
		y_pIo->databuff.buf = (char*)pData;
		y_pIo->databuff.len = len;
		return WSASend(sk, &y_pIo->databuff, 1, &lpNumberOfBytesSent, dwFlags, &y_pIo->overlapped, lzz_nullptr) == WSA_IO_PENDING;
	}
	else
	{
	int state = send(sk, static_cast<char*>(pData), len, 0);
	return state == len;
	}

}

bool lzz_ServerSocket::TcpRecv(void* pData, int len, lzz_Factory * f, int ActionType)
{
	lzz_ZeroMemory(y_pIo,sizeof(lzz_PER_IO_OPERATEION_DATA));
	y_pIo->databuff.buf = (char*)pData;
	y_pIo->databuff.len = len;
	y_pIo->factory = f;
	y_pIo->ActionType = ActionType;
	DWORD lpFlags = 0;
	return WSARecv(sk, &y_pIo->databuff, 1, &y_pIo->bytesSend, &lpFlags, &y_pIo->overlapped, lzz_nullptr) == WSA_IO_PENDING;
}

bool lzz_ServerSocket::TcpSend(void* pData, int len, lzz_Factory* f, int ActionType)
{
	y_pIo->databuff.buf = (char*)pData;
	y_pIo->databuff.len = len;
	y_pIo->factory = f;
	y_pIo->ActionType = ActionType;
	return WSASend(sk, &y_pIo->databuff, 1, &y_pIo->bytesSend, 0, &y_pIo->overlapped, lzz_nullptr) == WSA_IO_PENDING;
}

bool lzz_ServerSocket::TcpRecv(void* pData,int len)
{
	if (y_pHaandle != lzz_nullptr)
	{
		lzz_Memcpy(y_pIo->buffer, pData, len);
		return WSARecv(sk, &y_pIo->databuff, 1, &y_pIo->bytesSend, 0, &y_pIo->overlapped, lzz_nullptr) == WSA_IO_PENDING;
	}
	else
	{
		for (int i = 0; i < len;i++)
		{
			if (recv(sk, static_cast<char*>(pData) + i, 1, 0) <= 0)
			{
				return false;
			}
		}
		return true;
	}

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
	if (sendto(sk, s, len + 8, 0, pAddress, sizeof(SOCKADDR)) == SOCKET_ERROR)
		throw 1;
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
