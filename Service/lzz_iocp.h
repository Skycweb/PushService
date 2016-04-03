#pragma once

/************************************************************************

FileName:iocp.h
Author	:eliteYang
http://www.cppfans.org

************************************************************************/
#ifndef __IOCP_H__
#define __IOCP_H__
#include <WinSock2.h>
#pragma comment( lib, "Ws2_32.lib" )
#include "../include/base.h"

#define DefaultPort 8023
#define DataBuffSize 8 * 1024

typedef struct
{
	OVERLAPPED overlapped;
	WSABUF databuff;
	CHAR buffer[DataBuffSize];
	DWORD bytesSend;
	DWORD bytesRecv;
}PER_IO_OPERATEION_DATA, *LPPER_IO_OPERATION_DATA;

typedef struct
{
	SOCKET socket;
}PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

#endif