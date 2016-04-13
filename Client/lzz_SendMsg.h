#pragma once
#ifndef  _lzz_SendMsg_
#define  _lzz_SendMsg_
#include "../include/base.h";
#include "../include/lzz_Factory.h"
#include "lzz_ClientSocket.h"


class lzz_SendMsg : public lzz_Factory
{
private:
	
	bool isSend;
public:
	lzz_SendMsg();
	///��������
	bool Send(GUID RecvUserId, char* SendData, int DataLen);
	///��������
	bool Recv(GUID MsgId,char* SendData,int DataLen);
	void onLoad() override;
	virtual ~lzz_SendMsg();
};


#endif