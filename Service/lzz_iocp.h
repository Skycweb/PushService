#pragma once

/************************************************************************

FileName:iocp.h
Author	:eliteYang
http://www.cppfans.org

************************************************************************/
#ifndef __IOCP_H__
#define __IOCP_H__

#include "../include/base.h"
#include <string>
#define DefaultPort 8023
#define DataBuffSize 8 * 1024

typedef struct
{
	OVERLAPPED overlapped;
	WSABUF databuff;
	CHAR buffer[DataBuffSize];
	DWORD bytesSend;
	DWORD bytesRecv;
	GUID id;
}PER_IO_OPERATEION_DATA, *LPPER_IO_OPERATION_DATA;

typedef struct
{
	SOCKET socket;
}PER_HANDLE_DATA, *LPPER_HANDLE_DATA;

#endif