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
	��ʼ��
	*/
	virtual void init(lzz_SocketInterface*,lzz_ClientList*,char*,SOCKADDR*);//��ʼ��
	virtual void BindView();
	virtual void backFunction(int actionType);///IOCP�ص� ����
protected:
	SOCKADDR address_sockaddr_;//�����ߵ�ַ
	lzz_SocketInterface *sk = lzz_nullptr;//�����ߵ�ַ
	lzz_ClientList *cl = lzz_nullptr;//���з������б�

	char *respone = lzz_nullptr;//����ֵ
	char *request = lzz_nullptr;//����ֱ
	GUID VisitorId;//������ID
	GUID SessionId;//�����¼�ID
};

