#pragma once
#include  "base.h"
#include "../Service/lzz_ServerSocket.h"
#include "lzz_ClientList.h"
#include "lzz_Object.h"

class lzz_Factory:public lzz_Object
{
public:
	lzz_Factory();
	virtual ~lzz_Factory();
	virtual void onLoad();
	/*
	初始化
	*/
	virtual void init(lzz_SocketInterface*,lzz_ClientList*,char*,SOCKADDR*);//初始化
	virtual void BindView();
protected:
	SOCKADDR address_sockaddr_;//访问者地址
	lzz_SocketInterface *sk = lzz_nullptr;//访问者地址
	lzz_ClientList *cl = lzz_nullptr;//所有访问者列表

	char *respone = lzz_nullptr;//返回值
	char *request = lzz_nullptr;//访问直
	GUID VisitorId;//访问者ID
	GUID SessionId;//访问事件ID
};

