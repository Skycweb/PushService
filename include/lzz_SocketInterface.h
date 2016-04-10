#pragma once
#include "base.h"
#define _IOCP_

class lzz_SocketInterface
{
public:
	lzz_SocketInterface();

	virtual ~lzz_SocketInterface();
	/*等待TCP连接*/
    virtual void Accept(SOCKET *s,SOCKADDR *address);
	/*发送信息*/
	virtual bool TcpSend(void *pData, int len);
	/*接收信息*/
	virtual bool TcpSend(void *pData, int len, ActionType a);
	/*接收信息*/
	virtual bool TcpRecv(void *pData, int len);
	/*发送信息*/
	virtual void UdpSend(void* pData, int len, ActionType at, SOCKADDR* pAddress);
	/*发送信息*/
	virtual void UdpSend(void *pData, int len, ActionType at);
	/*接收信息*/
	virtual void UdpRecv(void *pData, int len, SOCKADDR *pAddress);
protected:
	static WSADATA wsa;
private:
	static int SocketStartup;
	static int SocketLen;
};
