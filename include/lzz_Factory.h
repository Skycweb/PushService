

#ifndef _lzz_Factory_
#define _lzz_Factory_

#include  "base.h"
#include "lzz_SocketInterface.h"
#include "lzz_ClientList.h"
#include "lzz_Object.h"
class lzz_SocketInterface;
class lzz_Factory:public lzz_Object
{
public:
	lzz_Factory();
	virtual ~lzz_Factory();
	virtual void onLoad();
	/*��ʼ��*/
	virtual void init(lzz_SocketInterface *_sk,lzz_ClientList *_cl,char *reqest,SOCKADDR* address);
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

#endif