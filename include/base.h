#pragma once

#ifndef base_H
#define base_H
#include <stdio.h>
#include <iostream>
#include <objbase.h>
#include <process.h>

//#define lzzgcc // gcc开关
//#define waiwang

#ifndef lzz_ServiceTcpIp
#ifdef  waiwang
#define lzz_ServiceTcpIp  "120.76.96.128"
#else
#define lzz_ServiceTcpIp  "192.168.2.102"
#endif
#endif

#ifndef lzz_ServiceTcpPort
#define lzz_ServiceTcpPort  8023
#endif
#ifndef lzz_ServiceUdpId
#ifdef waiwang
#define lzz_ServiceUdpId  "120.76.96.128"
#else
#define lzz_ServiceUdpId  "192.168.0.168"
#endif
#endif

#ifndef lzz_ServiceUdpPort
#define lzz_ServiceUdpPort  8024
#endif


#ifndef  lzz_out
#define  lzz_out std::cout
#endif

#ifndef lzz_in
#define  lzz_in std::cin
#endif


#ifndef lzz_endline
#define lzz_endline std::endl
#endif

#ifndef lzz_ZeroMemory
#define lzz_ZeroMemory(p,len) memset((p),0,(len))
#endif

#ifndef lzz_Memcpy

#define lzz_Memcpy(d,s,len) memcpy((d),(s),(len))

#endif

#ifndef lzz_NewGuid
#define lzz_NewGuid(guid) CoCreateGuid((guid))
#endif

#ifndef lzz_Strcmp
#define lzz_Strcmp(s1,s2) strcmp((s1),(s2))
#endif

#ifndef lzz_Memcmp
#define lzz_Memcmp(s1,s2,size) memcmp((s1),(s2),(size))
#endif

#ifndef lzz_Beginthread
#define lzz_Beginthread(func,object) _beginthread((func), 0, (object))
#endif

#ifndef lzz_Endthreadex
#define lzz_Endthreadex(_HANDLE) _endthreadex((_HANDLE))
#endif

#ifndef lzz_Delete
#define lzz_Delete(p){ if(p){delete p;p = lzz_nullptr;}}
#endif

#ifndef lzz_ARRAY_LEN
#define lzz_ARRAY_LEN(_array,len) {len = (sizeof(_array) / sizeof(_array[0]));}
#endif

#ifndef lzz_Deletes
#define lzz_Deletes(p){ if(p){delete[] p;}}
#endif




#ifndef lzz_nullptr
#ifndef lzzgcc
#define lzz_nullptr nullptr
#else
#define lzz_nullptr NULL
#endif
#endif

#ifndef lzz_sleep
#ifndef  lzzgcc
#define lzz_sleep(s) ::Sleep((s))
#else
#include <unistd.h>
#define lzz_sleep(s) usleep((s));
#endif
#endif


void lzz_STR_2_GUID(wchar_t* cstr, GUID *stGuid);



namespace _ActionType {
	//访问类型
	enum ActionType_
	{
		None = 0,
		Heartbeat = 1,
		PushAction = 2 //推送
	};
}
typedef _ActionType::ActionType_ ActionType;
/*
推送类型
*/
namespace _pushType
{
	enum _pushType
	{
		None = 0,
		Add = 1,//添加好友推送
		Delete = 2//删除好友推送
	};
}
typedef _pushType::_pushType pushType;

#endif