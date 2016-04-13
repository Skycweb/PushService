#pragma once
#ifndef  _lzz_SocketInterface_
#define  _lzz_SocketInterface_
#include "base.h"
#define _IOCP_
#include "lzz_Factory.h"

#define DataBuffSize 1024

class lzz_Factory;
typedef struct
{
	OVERLAPPED overlapped;
	WSABUF databuff;
	CHAR buffer[DataBuffSize];
	DWORD bytesSend;
	DWORD bytesRecv;
	lzz_Factory* factory;
	int ActionType = 0;
}lzz_PER_IO_OPERATEION_DATA, *lzz_LPPER_IO_OPERATION_DATA;

typedef struct
{
	SOCKET socket;
}lzz_PER_HANDLE_DATA, *lzz_LPPER_HANDLE_DATA;

class lzz_SocketInterface
{
public:
	lzz_SocketInterface();

	virtual ~lzz_SocketInterface();
	/*�ȴ�TCP����*/
    virtual void Accept(SOCKET *s,SOCKADDR *address);
	/*������Ϣ*/
	virtual bool TcpSend(void *pData, int len);
	/*������Ϣ*/
	virtual bool TcpSend(void *pData, int len,lzz_Factory * f,int ActionType);
	/*������Ϣ*/
	virtual bool TcpSend(void *pData, int len, ActionType a);
	/*������Ϣ*/
	virtual bool TcpRecv(void *pData, int len);
	/*������Ϣ*/
	virtual bool TcpRecv(void *pData, int len, lzz_Factory * f, int ActionType);
	/*������Ϣ*/
	virtual void UdpSend(void* pData, int len, ActionType at, SOCKADDR* pAddress);
	/*������Ϣ*/
	virtual void UdpSend(void *pData, int len, ActionType at);
	/*������Ϣ*/
	virtual void UdpRecv(void *pData, int len, SOCKADDR *pAddress);
	lzz_LPPER_IO_OPERATION_DATA y_pIo = lzz_nullptr;
	lzz_LPPER_HANDLE_DATA y_pHaandle = lzz_nullptr;
protected:
	static WSADATA wsa;

private:
	static int SocketStartup;
	static int SocketLen;
};


#endif